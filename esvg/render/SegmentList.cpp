/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/SegmentList.h>
#include <esvg/debug.h>


#undef __class__
#define __class__	"rerder::SegmentList"

bool sortSegmentFunction(const esvg::render::Segment& _e1, const esvg::render::Segment& _e2) {
	return _e1.p0.y() < _e2.p0.y();
}

esvg::render::SegmentList::SegmentList() {
	
}

void esvg::render::SegmentList::addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1) {
	// Skip horizontal Segments
	if (_pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	m_data.push_back(Segment(_pos0.m_pos, _pos1.m_pos));
}

void esvg::render::SegmentList::createSegmentList(const esvg::render::PointList& _listPoint) {
	for (auto &it : _listPoint.m_data) {
		// Build Segments
		for (int32_t iii=0, jjj=it.size()-1;
		     iii < it.size();
		     jjj = iii++) {
			addSegment(it[jjj], it[iii]);
		}
	}
	// TODO : Check if it is really usefull ...
	std::sort(m_data.begin(), m_data.end(), sortSegmentFunction);
}

void esvg::render::SegmentList::createSegmentListStroke(esvg::render::PointList& _listPoint, float _width) {
	for (auto &itListPoint : _listPoint.m_data) {
		// generate for every point all the orthogonal elements
		//                                                                                   
		//     normal edge             *                 end path                            
		//                           * | *                      * * * * * * * * * * * * *    
		//                         *   |<--*----this                            |       *    
		//                       *     |     *                          this -->|       *    
		//                     *       *       *                                |       *    
		//                   *       . | .       *              . . . . . . . . *       *    
		//                 *       .   |   .       *                            |       *    
		//               *     A .     |     . B     *                          |       *    
		//                     .       *       .                                |       *    
		//                   .       *   *       .              * * * * * * * * * * * * *    
		//                         *       *                                                 
		//                       *           *                                               
		// TODO : Start and stop of the path ...
		for (int32_t idPevious=itListPoint.size()-1, idCurrent=0, idNext=1;
		     idCurrent < itListPoint.size();
		     idPevious = idCurrent++, idNext++) {
			if (idNext == itListPoint.size()) {
				idNext = 0;
			}
			if (    itListPoint[idCurrent].m_type == esvg::render::Point::type_join
			     || itListPoint[idCurrent].m_type == esvg::render::Point::type_interpolation) {
				if (idPevious < 0 ) {
					SVG_ERROR("an error occure a previous ID is < 0.... ");
					continue;
				}
				if (idNext >= itListPoint.size()) {
					SVG_ERROR("an error occure a next ID is >= nbPoint len .... ");
					continue;
				}
				//SVG_DEBUG("JOIN : id : prev/curr/next : " << idPevious << "/" << idCurrent << "/" << idNext);
				//SVG_DEBUG("JOIN : val : prev/curr/next : " << itListPoint[idPevious].m_pos << "/" << itListPoint[idCurrent].m_pos << "/" << itListPoint[idNext].m_pos);
				vec2 vecA = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				//SVG_DEBUG("JOIN : vecA : " << vecA);
				vecA.safeNormalize();
				vec2 vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				//SVG_DEBUG("JOIN : vecB : " << vecB);
				vecB.safeNormalize();
				vec2 vecC = vecA - vecB;
				//SVG_DEBUG("JOIN : vecC : " << vecC);
				if (vecC == vec2(0.0f, 0.0f)) {
					// special case: 1 line ...
					itListPoint[idCurrent].m_miterAxe = vec2(vecA.y(), vecA.x());
				} else {
					vecC.safeNormalize();
					itListPoint[idCurrent].m_miterAxe = vecC;
				}
				//SVG_DEBUG("JOIN : miterAxe " << itListPoint[idCurrent].m_miterAxe);
			} else if (itListPoint[idCurrent].m_type == esvg::render::Point::type_start) {
				vec2 vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_miterAxe = vec2(vecB.y(), -vecB.x());
			} else if (itListPoint[idCurrent].m_type == esvg::render::Point::type_stop) {
				if (idPevious < 0 ) {
					SVG_ERROR("an error occure a previous ID is < 0.... ");
					continue;
				}
				vec2 vecA = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				vecA.safeNormalize();
				itListPoint[idCurrent].m_miterAxe = vec2(vecA.y(), -vecA.x());
			} else {
				SVG_TODO("lklklklklkl");
			}
		}
		// create segment list:
		bool haveStartLine;
		vec2 leftPoint;
		vec2 rightPoint;
		if (itListPoint.size() > 0) {
			if (itListPoint.front().m_type == esvg::render::Point::type_join) {
				// cyclic path...
				if (    itListPoint.back().m_type == esvg::render::Point::type_join
				     || itListPoint.back().m_type == esvg::render::Point::type_interpolation) {
					leftPoint =   itListPoint.back().m_pos
					            + itListPoint.back().m_miterAxe*_width*0.5f;
					rightPoint =   itListPoint.back().m_pos
					             - itListPoint.back().m_miterAxe*_width*0.5f;
				} else {
					SVG_ERROR("Start list point with a join, but last lement is not a join");
				}
			}
		}
		for (auto &it : itListPoint) {
			switch (it.m_type) {
				case esvg::render::Point::type_single:
					// just do nothing ....
					SVG_VERBOSE("Find Single " << it.m_pos);
					break;
				case esvg::render::Point::type_start:
					{
						SVG_VERBOSE("Find Start " << it.m_pos);
						if (haveStartLine == true) {
							// close previous :
							SVG_WARNING(" find a non close path ...");
							addSegment(leftPoint, rightPoint);
						}
						haveStartLine = true;
						// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
						leftPoint =   it.m_pos
						            + it.m_miterAxe*_width*0.5f;
						rightPoint =   it.m_pos
						             - it.m_miterAxe*_width*0.5f;
						addSegment(leftPoint, rightPoint);
						SVG_VERBOSE("    segment :" << leftPoint << " -> " << rightPoint);
					}
					break;
				case esvg::render::Point::type_stop:
					{
						SVG_VERBOSE("Find Stop " << it.m_pos);
						if (haveStartLine == false) {
							SVG_WARNING("find close path without start part ...");
							break;
						}
						haveStartLine = false;
						// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
						vec2 left =   it.m_pos
						            + it.m_miterAxe*_width*0.5f;
						vec2 right =   it.m_pos
						             - it.m_miterAxe*_width*0.5f;
						//Draw from previous point:
						addSegment(leftPoint, left);
						SVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
						addSegment(right, rightPoint);
						SVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
						leftPoint = left;
						rightPoint = right;
						// end line ...
						addSegment(rightPoint, leftPoint);
						SVG_VERBOSE("    segment :" << rightPoint << " -> " << leftPoint);
					}
					break;
				case esvg::render::Point::type_interpolation:
					{
						SVG_VERBOSE("Find interpolation " << it.m_pos);
						// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
						vec2 left =   it.m_pos
						            + it.m_miterAxe*_width*0.5f;
						vec2 right =   it.m_pos
						             - it.m_miterAxe*_width*0.5f;
						//Draw from previous point:
						addSegment(leftPoint, left);
						SVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
						addSegment(right, rightPoint);
						SVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
						leftPoint = left;
						rightPoint = right;
					}
					break;
				case esvg::render::Point::type_join:
					{
						SVG_VERBOSE("Find Join " << it.m_pos);
						// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
						vec2 left =   it.m_pos
						            + it.m_miterAxe*_width*0.5f;
						vec2 right =   it.m_pos
						             - it.m_miterAxe*_width*0.5f;
						//Draw from previous point:
						addSegment(leftPoint, left);
						SVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
						addSegment(right, rightPoint);
						SVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
						leftPoint = left;
						rightPoint = right;
					}
					break;
			}
		}
	}
	// TODO : Check if it is really usefull ...
	std::sort(m_data.begin(), m_data.end(), sortSegmentFunction);
}



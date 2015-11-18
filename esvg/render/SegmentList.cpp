/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/SegmentList.h>
#include <esvg/debug.h>


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

void esvg::render::SegmentList::createSegmentList(const std::vector<esvg::render::Point>& _listPoint) {
	// Build Segments
	for (int32_t iii=0, jjj=_listPoint.size()-1;
	     iii < _listPoint.size();
	     jjj = iii++) {
		addSegment(_listPoint[jjj], _listPoint[iii]);
	}
	// TODO : Check if it is really usefull ...
	std::sort(m_data.begin(), m_data.end(), sortSegmentFunction);
}

void esvg::render::SegmentList::createSegmentListStroke(std::vector<esvg::render::Point>& _listPoint) {
	// generate for every point all the orthogonal elements
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
	for (int32_t idPevious=-1, idCurrent=0, idNext=1;
	     idCurrent < _listPoint.size();
	     idPevious++, idCurrent++, idNext++) {
		if (    _listPoint[idCurrent].m_type == esvg::render::Point::type_join
		     || _listPoint[idCurrent].m_type == esvg::render::Point::type_interpolation) {
			if (idPevious < 0 ) {
				SVG_ERROR("an error occure a previous ID is < 0.... ");
				continue;
			}
			if (idNext >= _listPoint.size()) {
				SVG_ERROR("an error occure a next ID is >= nbPoint len .... ");
				continue;
			}
			vec2 vecA = _listPoint[idCurrent].m_pos - _listPoint[idPevious].m_pos;
			vecA.safeNormalize();
			vec2 vecB = _listPoint[idNext].m_pos - _listPoint[idCurrent].m_pos;
			vecB.safeNormalize();
			vec2 vecC = vecA - vecB;
			if (vecC == vec2(0,0)) {
				// special case: 1 line ...
				_listPoint[idCurrent].m_miterAxe = vec2(vecA.y(), vecA.x());
			} else {
				vecC.safeNormalize();
				_listPoint[idCurrent].m_miterAxe = vecC;
			}
		} else if (_listPoint[idCurrent].m_type == esvg::render::Point::type_start) {
			vec2 vecB = _listPoint[idNext].m_pos - _listPoint[idCurrent].m_pos;
			vecB.safeNormalize();
			_listPoint[idCurrent].m_miterAxe = vec2(vecB.y(), vecB.x());
		} else if (_listPoint[idCurrent].m_type == esvg::render::Point::type_stop) {
			if (idPevious < 0 ) {
				SVG_ERROR("an error occure a previous ID is < 0.... ");
				continue;
			}
			vec2 vecA = _listPoint[idCurrent].m_pos - _listPoint[idPevious].m_pos;
			vecA.safeNormalize();
			_listPoint[idCurrent].m_miterAxe = vec2(vecA.y(), vecA.x());
		} else {
			SVG_TODO("lklklklklkl");
		}
	}
	float lineWidth = 5.0f;
	// create segment list:
	bool haveStartLine;
	vec2 leftPoint;
	vec2 rightPoint;
	for (int32_t iii=0;
	     iii < _listPoint.size();
	     ++iii) {
		switch (_listPoint[iii].m_type) {
			case esvg::render::Point::type_single:
				// just do nothing ....
				SVG_VERBOSE("[" << iii << "] Find Single " << _listPoint[iii].m_pos);
				break;
			case esvg::render::Point::type_start:
				{
					SVG_VERBOSE("[" << iii << "] Find Start " << _listPoint[iii].m_pos);
					if (haveStartLine == true) {
						// close previous :
						SVG_WARNING(" find a non close path ...");
						addSegment(leftPoint, rightPoint);
					}
					haveStartLine = true;
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					leftPoint =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					rightPoint =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					addSegment(leftPoint, rightPoint);
					SVG_VERBOSE("    segment :" << leftPoint << " -> " << rightPoint);
				}
				break;
			case esvg::render::Point::type_stop:
				{
					SVG_VERBOSE("[" << iii << "] Find Stop " << _listPoint[iii].m_pos);
					if (haveStartLine == true) {
						SVG_WARNING("find close path without start part ...");
						break;
					}
					haveStartLine = false;
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					vec2 left =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					vec2 right =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
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
					SVG_VERBOSE("[" << iii << "] Find interpolation " << _listPoint[iii].m_pos);
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					vec2 left =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					vec2 right =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
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
					SVG_VERBOSE("[" << iii << "] Find Join " << _listPoint[iii].m_pos);
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					vec2 left =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					vec2 right =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
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
	// TODO : Check if it is really usefull ...
	std::sort(m_data.begin(), m_data.end(), sortSegmentFunction);
}



/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/SegmentList.h>
#include <esvg/debug.h>
#include <etk/math/Matrix2.h>

esvg::render::SegmentList::SegmentList() {
	
}
#ifdef DEBUG
	void esvg::render::SegmentList::addSegment(const vec2& _pos0, const vec2& _pos1) {
		m_data.push_back(Segment(_pos0, _pos1));
	}
#endif

void esvg::render::SegmentList::addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1) {
	// Skip horizontal Segments
	if (_pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	m_data.push_back(Segment(_pos0.m_pos, _pos1.m_pos));
}

void esvg::render::SegmentList::addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1, bool _disableHorizontal) {
	// Skip horizontal Segments
	if (    _disableHorizontal == true
	     && _pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	m_data.push_back(Segment(_pos0.m_pos, _pos1.m_pos));
}

std::pair<vec2, vec2> esvg::render::SegmentList::getViewPort() {
	std::pair<vec2, vec2> out(vec2(9999999999.0,9999999999.0),vec2(-9999999999.0,-9999999999.0));
	for (auto &it : m_data) {
		out.first.setMin(it.p0);
		out.second.setMax(it.p0);
		out.first.setMin(it.p1);
		out.second.setMax(it.p1);
	}
	return out;
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
}

static vec2 getIntersect(const vec2& _point1,
                         const vec2& _vect1,
                         const vec2& _point2,
                         const vec2& _vect2) {
	float diviseur = _vect1.x() * _vect2.y() - _vect1.y() * _vect2.x();
	if(diviseur != 0.0f) {
		float mmm = (   _vect1.x() * _point1.y()
		              - _vect1.x() * _point2.y()
		              - _vect1.y() * _point1.x()
		              + _vect1.y() * _point2.x()
		            ) / diviseur;
		return vec2(_point2 + _vect2 * mmm);
	}
	ESVG_ERROR("Get divider / 0.0f");
	return _point2;
}

void esvg::render::SegmentList::createSegmentListStroke(const vec2& _point1,
                                                        const vec2& _point2,
                                                        const vec2& _center,
                                                        float _width,
                                                        bool _isStart) {
	int32_t nbDot = int32_t(_width);
	if (nbDot <= 2) {
		nbDot = 2;
	}
	float angleToDraw = acos((_point1 - _center).safeNormalize().dot((_point2 - _center).safeNormalize()));
	float baseAngle = angleToDraw/float(nbDot);
	float iii;
	vec2 axe = (_point1 - _center).safeNormalize();
	vec2 ppp1(_point1);
	vec2 ppp2(_point2);
	for (iii=baseAngle; iii<angleToDraw; iii+=baseAngle) {
		mat2 tmpMat;
		if (_isStart == true) {
			tmpMat = etk::mat2Rotate(-iii);
		} else {
			tmpMat = etk::mat2Rotate(iii);
		}
		vec2 axeRotate = tmpMat * axe;
		ppp2 =   _center
		       + axeRotate*_width*0.5f;
		if (_isStart == true) {
			addSegment(ppp2, ppp1);
			ESVG_VERBOSE("    segment :" << ppp2 << " -> " << ppp1);
		} else {
			addSegment(ppp1, ppp2);
			ESVG_VERBOSE("    segment :" << ppp1 << " -> " << ppp2);
		}
		ppp1 = ppp2;
	}
	if (_isStart == true) {
		addSegment(_point2, ppp1);
		ESVG_VERBOSE("    segment :" << _point2 << " -> " << ppp1);
	} else {
		addSegment(ppp1, _point2);
		ESVG_VERBOSE("    segment :" << ppp1 << " -> " << _point2);
	}
}

void esvg::render::SegmentList::createSegmentListStroke(esvg::render::PointList& _listPoint,
                                                        float _width,
                                                        enum esvg::cap _cap,
                                                        enum esvg::join _join,
                                                        float _miterLimit) {
	for (auto &itListPoint : _listPoint.m_data) {
		// generate for every point all the orthogonal elements
		//                                                                                   
		//     normal edge             *                 end path                            
		//      (mitter)             * | *                      * * * * * * * * * * * * *    
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
		for (int32_t idPevious=itListPoint.size()-1, idCurrent=0, idNext=1;
		     idCurrent < itListPoint.size();
		     idPevious = idCurrent++, idNext++) {
			if (idNext == itListPoint.size()) {
				idNext = 0;
			}
			if (    itListPoint[idCurrent].m_type == esvg::render::Point::type::join
			     || itListPoint[idCurrent].m_type == esvg::render::Point::type::interpolation) {
				if (idPevious < 0 ) {
					ESVG_ERROR("an error occure a previous ID is < 0.... ");
					continue;
				}
				if (idNext >= itListPoint.size()) {
					ESVG_ERROR("an error occure a next ID is >= nbPoint len .... ");
					continue;
				}
				//ESVG_DEBUG("JOIN : id : prev/curr/next : " << idPevious << "/" << idCurrent << "/" << idNext);
				//ESVG_DEBUG("JOIN : val : prev/curr/next : " << itListPoint[idPevious].m_pos << "/" << itListPoint[idCurrent].m_pos << "/" << itListPoint[idNext].m_pos);
				vec2 vecA = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				//ESVG_DEBUG("JOIN : vecA : " << vecA);
				vecA.safeNormalize();
				vec2 vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				//ESVG_DEBUG("JOIN : vecB : " << vecB);
				vecB.safeNormalize();
				vec2 vecC = vecA - vecB;
				//ESVG_DEBUG("JOIN : vecC : " << vecC);
				if (vecC == vec2(0.0f, 0.0f)) {
					// special case: 1 line ...
					itListPoint[idCurrent].m_miterAxe = vec2(vecA.y(), vecA.x());
				} else {
					vecC.safeNormalize();
					itListPoint[idCurrent].m_miterAxe = vecC;
				}
				itListPoint[idCurrent].m_posPrevious = itListPoint[idPevious].m_pos;
				itListPoint[idCurrent].m_posNext = itListPoint[idNext].m_pos;
				vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_orthoAxeNext = vec2(vecB.y(), -vecB.x());
				vecB = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_orthoAxePrevious = vec2(vecB.y(), -vecB.x());
				//ESVG_DEBUG("JOIN : miterAxe " << itListPoint[idCurrent].m_miterAxe);
			} else if (itListPoint[idCurrent].m_type == esvg::render::Point::type::start) {
				itListPoint[idCurrent].m_posNext = itListPoint[idNext].m_pos;
				vec2 vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_miterAxe = vec2(vecB.y(), -vecB.x());
				itListPoint[idCurrent].m_orthoAxePrevious = itListPoint[idCurrent].m_miterAxe;
				itListPoint[idCurrent].m_orthoAxeNext = itListPoint[idCurrent].m_miterAxe;
			} else if (itListPoint[idCurrent].m_type == esvg::render::Point::type::stop) {
				if (idPevious < 0 ) {
					ESVG_ERROR("an error occure a previous ID is < 0.... ");
					continue;
				}
				itListPoint[idCurrent].m_posPrevious = itListPoint[idPevious].m_pos;
				vec2 vecA = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				vecA.safeNormalize();
				itListPoint[idCurrent].m_miterAxe = vec2(vecA.y(), -vecA.x());
				itListPoint[idCurrent].m_orthoAxePrevious = itListPoint[idCurrent].m_miterAxe;
				itListPoint[idCurrent].m_orthoAxeNext = itListPoint[idCurrent].m_miterAxe;
			} else {
				ESVG_TODO("Unsupported type of point ....");
			}
		}
		// create segment list:
		bool haveStartLine = false;
		vec2 leftPoint(0,0);
		vec2 rightPoint(0,0);
		if (itListPoint.size() > 0) {
			if (itListPoint.front().m_type == esvg::render::Point::type::join) {
				const esvg::render::Point& it = itListPoint.back();
				// Calculate the perpendiculary axis ...
				leftPoint =   itListPoint.back().m_pos
				            + itListPoint.back().m_orthoAxePrevious*_width*0.5f;
				rightPoint =   itListPoint.back().m_pos
				             - itListPoint.back().m_orthoAxePrevious*_width*0.5f;
				// cyclic path...
				if (it.m_type == esvg::render::Point::type::interpolation) {
					leftPoint  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
					rightPoint = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
				} else if (it.m_type == esvg::render::Point::type::join) {
					// Calculate the perpendiculary axis ...
					leftPoint =   it.m_pos
					            + it.m_orthoAxePrevious*_width*0.5f;
					rightPoint =   it.m_pos
					             - it.m_orthoAxePrevious*_width*0.5f;
					// project on the miter Axis ...
					switch (_join) {
						case esvg::join_miter:
							{
								vec2 left  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								vec2 right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								// Check the miter limit:
								float limitRight = (left - it.m_pos).length() / _width * 2.0f;
								float limitLeft  = (right - it.m_pos).length() / _width * 2.0f;
								ESVG_VERBOSE("    miter Limit: " << limitRight << " " << limitLeft << " <= " << _miterLimit);
								if (    limitRight <= _miterLimit
								     && limitLeft <= _miterLimit) {
									leftPoint  = left;
									rightPoint = right;
									break;
								} else {
									// BEVEL the miter point ...
								}
							}
						case esvg::join_round:
						case esvg::join_bevel:
							{
								vec2 axePrevious = (it.m_pos-it.m_posPrevious).safeNormalize();
								vec2 axeNext = (it.m_posNext - it.m_pos).safeNormalize();
								float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									rightPoint = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
									leftPoint  =   it.m_pos
									             + it.m_orthoAxeNext*_width*0.5f;
								} else {
									leftPoint  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
									rightPoint =   it.m_pos
									             - it.m_orthoAxeNext*_width*0.5f;
								}
								break;
							}
					}
				} else {
					ESVG_ERROR("Start list point with a join, but last lement is not a join");
				}
			}
		}
		for (auto &it : itListPoint) {
			switch (it.m_type) {
				case esvg::render::Point::type::single:
					// just do nothing ....
					ESVG_VERBOSE("Find Single " << it.m_pos);
					break;
				case esvg::render::Point::type::start:
					ESVG_VERBOSE("Find Start " << it.m_pos);
					if (haveStartLine == true) {
						// close previous :
						ESVG_WARNING(" find a non close path ...");
						addSegment(leftPoint, rightPoint);
					}
					haveStartLine = true;
					startStopPoint(leftPoint, rightPoint, it, _cap, _width, true);
					break;
				case esvg::render::Point::type::stop:
					ESVG_VERBOSE("Find Stop " << it.m_pos);
					if (haveStartLine == false) {
						ESVG_WARNING("find close path without start part ...");
						break;
					}
					haveStartLine = false;
					startStopPoint(leftPoint, rightPoint, it, _cap, _width, false);
					break;
				case esvg::render::Point::type::interpolation:
					{
						ESVG_VERBOSE("Find interpolation " << it.m_pos);
						vec2 left  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
						vec2 right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
						//Draw from previous point:
						addSegment(leftPoint, left);
						ESVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
						addSegment(right, rightPoint);
						ESVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
						leftPoint = left;
						rightPoint = right;
					}
					break;
				case esvg::render::Point::type::join:
					ESVG_VERBOSE("Find join " << it.m_pos);
					switch (_join) {
						case esvg::join_miter:
							{
								vec2 left  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								vec2 right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								// Check the miter limit:
								float limitRight = (left - it.m_pos).length() / _width * 2.0f;
								float limitLeft  = (right - it.m_pos).length() / _width * 2.0f;
								ESVG_VERBOSE("    miter Limit: " << limitRight << " " << limitLeft << " <= " << _miterLimit);
								if (    limitRight <= _miterLimit
								     && limitLeft <= _miterLimit) {
									//Draw from previous point:
									addSegment(leftPoint, left);
									ESVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
									addSegment(right, rightPoint);
									ESVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
									leftPoint = left;
									rightPoint = right;
									break;
								} else {
									// We do a bevel join ...
									ESVG_VERBOSE("    Find miter Limit ... ==> create BEVEL");
								}
							}
						case esvg::join_round:
						case esvg::join_bevel:
							{
								vec2 axePrevious = (it.m_pos-it.m_posPrevious).safeNormalize();
								vec2 axeNext = (it.m_posNext - it.m_pos).safeNormalize();
								float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									vec2 right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
									vec2 left1 =   it.m_pos
									             + it.m_orthoAxePrevious*_width*0.5f;
									vec2 left2 =   it.m_pos
									             + it.m_orthoAxeNext*_width*0.5f;
									//Draw from previous point:
									addSegment(leftPoint, left1);
									ESVG_VERBOSE("    segment :" << leftPoint << " -> " << left1);
									if (_join != esvg::join_round) {
										// Miter and bevel:
										addSegment(left1, left2);
										ESVG_VERBOSE("    segment :" << left1 << " -> " << left2);
									}else {
										createSegmentListStroke(left1,
										                        left2,
										                        it.m_pos,
										                        _width,
										                        false);
									}
									addSegment(right, rightPoint);
									ESVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
									leftPoint = left2;
									rightPoint = right;
								} else {
									vec2 left   = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
									vec2 right1 =   it.m_pos
									              - it.m_orthoAxePrevious*_width*0.5f;
									vec2 right2 =   it.m_pos
									              - it.m_orthoAxeNext*_width*0.5f;//Draw from previous point:
									addSegment(leftPoint, left);
									ESVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
									addSegment(right1, rightPoint);
									ESVG_VERBOSE("    segment :" << right1 << " -> " << rightPoint);
									if (_join != esvg::join_round) {
										// Miter and bevel:
										addSegment(right2, right1);
										ESVG_VERBOSE("    segment :" << right2 << " -> " << right1);
									} else {
										createSegmentListStroke(right1,
										                        right2,
										                        it.m_pos,
										                        _width,
										                        true);
									}
									leftPoint = left;
									rightPoint = right2;
								}
							}
							break;
					}
					break;
			}
		}
	}
}

void esvg::render::SegmentList::startStopPoint(vec2& _leftPoint,
                                               vec2& _rightPoint,
                                               const esvg::render::Point& _point,
                                               enum esvg::cap _cap,
                                               float _width,
                                               bool _isStart) {
	switch (_cap) {
		case esvg::cap_butt:
			{
				vec2 left =   _point.m_pos
				            + _point.m_miterAxe*_width*0.5f;
				vec2 right =   _point.m_pos
				             - _point.m_miterAxe*_width*0.5f;
				if (_isStart == false) {
					//Draw from previous point:
					addSegment(_leftPoint, left);
					ESVG_VERBOSE("    segment :" << _leftPoint << " -> " << left);
					addSegment(right, _rightPoint);
					ESVG_VERBOSE("    segment :" << right << " -> " << _rightPoint);
				}
				_leftPoint = left;
				_rightPoint = right;
			}
			if (_isStart == false) {
				addSegment(_leftPoint, _rightPoint);
				ESVG_VERBOSE("    segment :" << _leftPoint << " -> " << _rightPoint);
			} else {
				addSegment(_rightPoint, _leftPoint);
				ESVG_VERBOSE("    segment :" << _rightPoint << " -> " << _leftPoint);
			}
			break;
		case esvg::cap_round:
			{
				if (_isStart == false) {
					vec2 left =   _point.m_pos
					            + _point.m_miterAxe*_width*0.5f;
					vec2 right =   _point.m_pos
					             - _point.m_miterAxe*_width*0.5f;
					if (_isStart == false) {
						//Draw from previous point:
						addSegment(_leftPoint, left);
						ESVG_VERBOSE("    segment :" << _leftPoint << " -> " << left);
						addSegment(right, _rightPoint);
						ESVG_VERBOSE("    segment :" << right << " -> " << _rightPoint);
					}
					_leftPoint = left;
					_rightPoint = right;
				}
				int32_t nbDot = int32_t(_width);
				if (nbDot <= 2) {
					nbDot = 2;
				}
				float baseAngle = M_PI/float(nbDot);
				float iii;
				_leftPoint =   _point.m_pos
				             + _point.m_miterAxe*_width*0.5f;
				_rightPoint =   _point.m_pos
				              - _point.m_miterAxe*_width*0.5f;
				createSegmentListStroke(_leftPoint,
				                        _rightPoint,
				                        _point.m_pos,
				                        _width,
				                        _isStart);
			}
			break;
		case esvg::cap_square:
			{
				vec2 nextAxe;
				if (_isStart == true) {
					nextAxe = _point.m_posNext - _point.m_pos;
				} else {
					nextAxe = _point.m_posPrevious - _point.m_pos;
				}
				vec2 left =   _point.m_pos
				            + _point.m_miterAxe*_width*0.5f;
				vec2 right =   _point.m_pos
				             - _point.m_miterAxe*_width*0.5f;
				mat2 tmpMat = etk::mat2Translate(nextAxe.safeNormalize()*_width*-0.5f);
				left = tmpMat*left;
				right = tmpMat*right;
				if (_isStart == false) {
					if (_isStart == false) {
						//Draw from previous point:
						addSegment(_leftPoint, left);
						ESVG_VERBOSE("    segment :" << _leftPoint << " -> " << left);
						addSegment(right, _rightPoint);
						ESVG_VERBOSE("    segment :" << right << " -> " << _rightPoint);
					}
				}
				_leftPoint = left;
				_rightPoint = right;
				if (_isStart == false) {
					addSegment(_leftPoint, _rightPoint);
					ESVG_VERBOSE("    segment :" << _leftPoint << " -> " << _rightPoint);
				} else {
					addSegment(_rightPoint, _leftPoint);
					ESVG_VERBOSE("    segment :" << _rightPoint << " -> " << _leftPoint);
				}
				ESVG_VERBOSE("    segment :" << _leftPoint << " -> " << _rightPoint);
			}
			break;
		default:
			ESVG_ERROR(" Undefined CAP TYPE");
			break;
	}
}

void esvg::render::SegmentList::applyMatrix(const mat2& _transformationMatrix) {
	for (auto &it : m_data) {
		it.applyMatrix(_transformationMatrix);
	}
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/SegmentList.hpp>
#include <esvg/debug.hpp>
#include <etk/math/Matrix2x3.hpp>

esvg::render::SegmentList::SegmentList() {
	
}
#ifdef DEBUG
	void esvg::render::SegmentList::addSegment(const Vector2f& _pos0, const Vector2f& _pos1) {
		m_data.pushBack(Segment(_pos0, _pos1));
	}
#endif

void esvg::render::SegmentList::addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1) {
	// Skip horizontal Segments
	if (_pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	m_data.pushBack(Segment(_pos0.m_pos, _pos1.m_pos));
}

void esvg::render::SegmentList::addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1, bool _disableHorizontal) {
	// Skip horizontal Segments
	if (    _disableHorizontal == true
	     && _pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	m_data.pushBack(Segment(_pos0.m_pos, _pos1.m_pos));
}

etk::Pair<Vector2f, Vector2f> esvg::render::SegmentList::getViewPort() {
	etk::Pair<Vector2f, Vector2f> out(Vector2f(9999999999.0,9999999999.0),Vector2f(-9999999999.0,-9999999999.0));
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
		for (size_t iii=0, jjj=it.size()-1;
		     iii < it.size();
		     jjj = iii++) {
			addSegment(it[jjj], it[iii]);
		}
	}
}

static Vector2f getIntersect(const Vector2f& _point1,
                         const Vector2f& _vect1,
                         const Vector2f& _point2,
                         const Vector2f& _vect2) {
	float diviseur = _vect1.x() * _vect2.y() - _vect1.y() * _vect2.x();
	if(diviseur != 0.0f) {
		float mmm = (   _vect1.x() * _point1.y()
		              - _vect1.x() * _point2.y()
		              - _vect1.y() * _point1.x()
		              + _vect1.y() * _point2.x()
		            ) / diviseur;
		return Vector2f(_point2 + _vect2 * mmm);
	}
	Log.error("Get divider / 0.0f");
	return _point2;
}

void esvg::render::SegmentList::createSegmentListStroke(const Vector2f& _point1,
                                                        const Vector2f& _point2,
                                                        const Vector2f& _center,
                                                        float _width,
                                                        bool _isStart) {
	int32_t nbDot = int32_t(_width);
	if (nbDot <= 2) {
		nbDot = 2;
	}
	float angleToDraw = acos((_point1 - _center).safeNormalize().dot((_point2 - _center).safeNormalize()));
	float baseAngle = angleToDraw/float(nbDot);
	float iii;
	Vector2f axe = (_point1 - _center).safeNormalize();
	Vector2f ppp1(_point1);
	Vector2f ppp2(_point2);
	for (iii=baseAngle; iii<angleToDraw; iii+=baseAngle) {
		mat2x3 tmpMat;
		if (_isStart == true) {
			tmpMat = etk::mat2x3Rotate(-iii);
		} else {
			tmpMat = etk::mat2x3Rotate(iii);
		}
		Vector2f axeRotate = tmpMat * axe;
		ppp2 =   _center
		       + axeRotate*_width*0.5f;
		if (_isStart == true) {
			addSegment(ppp2, ppp1);
			Log.verbose("    segment :" << ppp2 << " -> " << ppp1);
		} else {
			addSegment(ppp1, ppp2);
			Log.verbose("    segment :" << ppp1 << " -> " << ppp2);
		}
		ppp1 = ppp2;
	}
	if (_isStart == true) {
		addSegment(_point2, ppp1);
		Log.verbose("    segment :" << _point2 << " -> " << ppp1);
	} else {
		addSegment(ppp1, _point2);
		Log.verbose("    segment :" << ppp1 << " -> " << _point2);
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
		for (int64_t idPevious=itListPoint.size()-1, idCurrent=0, idNext=1;
		     idCurrent < int64_t(itListPoint.size());
		     idPevious = idCurrent++, idNext++) {
			if (idNext == int64_t(itListPoint.size())) {
				idNext = 0;
			}
			if (    itListPoint[idCurrent].m_type == esvg::render::Point::type::join
			     || itListPoint[idCurrent].m_type == esvg::render::Point::type::interpolation) {
				if (idPevious < 0 ) {
					Log.error("an error occure a previous ID is < 0.... ");
					continue;
				}
				if (idNext >= int64_t(itListPoint.size())) {
					Log.error("an error occure a next ID is >= nbPoint len .... ");
					continue;
				}
				//Log.debug("JOIN : id : prev/curr/next : " << idPevious << "/" << idCurrent << "/" << idNext);
				//Log.debug("JOIN : val : prev/curr/next : " << itListPoint[idPevious].m_pos << "/" << itListPoint[idCurrent].m_pos << "/" << itListPoint[idNext].m_pos);
				Vector2f vecA = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				//Log.debug("JOIN : vecA : " << vecA);
				vecA.safeNormalize();
				Vector2f vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				//Log.debug("JOIN : vecB : " << vecB);
				vecB.safeNormalize();
				Vector2f vecC = vecA - vecB;
				//Log.debug("JOIN : vecC : " << vecC);
				if (vecC == Vector2f(0.0f, 0.0f)) {
					// special case: 1 line ...
					itListPoint[idCurrent].m_miterAxe = Vector2f(vecA.y(), vecA.x());
				} else {
					vecC.safeNormalize();
					itListPoint[idCurrent].m_miterAxe = vecC;
				}
				itListPoint[idCurrent].m_posPrevious = itListPoint[idPevious].m_pos;
				itListPoint[idCurrent].m_posNext = itListPoint[idNext].m_pos;
				vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_orthoAxeNext = Vector2f(vecB.y(), -vecB.x());
				vecB = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_orthoAxePrevious = Vector2f(vecB.y(), -vecB.x());
				//Log.debug("JOIN : miterAxe " << itListPoint[idCurrent].m_miterAxe);
			} else if (itListPoint[idCurrent].m_type == esvg::render::Point::type::start) {
				itListPoint[idCurrent].m_posNext = itListPoint[idNext].m_pos;
				Vector2f vecB = itListPoint[idNext].m_pos - itListPoint[idCurrent].m_pos;
				vecB.safeNormalize();
				itListPoint[idCurrent].m_miterAxe = Vector2f(vecB.y(), -vecB.x());
				itListPoint[idCurrent].m_orthoAxePrevious = itListPoint[idCurrent].m_miterAxe;
				itListPoint[idCurrent].m_orthoAxeNext = itListPoint[idCurrent].m_miterAxe;
			} else if (itListPoint[idCurrent].m_type == esvg::render::Point::type::stop) {
				if (idPevious < 0 ) {
					Log.error("an error occure a previous ID is < 0.... ");
					continue;
				}
				itListPoint[idCurrent].m_posPrevious = itListPoint[idPevious].m_pos;
				Vector2f vecA = itListPoint[idCurrent].m_pos - itListPoint[idPevious].m_pos;
				vecA.safeNormalize();
				itListPoint[idCurrent].m_miterAxe = Vector2f(vecA.y(), -vecA.x());
				itListPoint[idCurrent].m_orthoAxePrevious = itListPoint[idCurrent].m_miterAxe;
				itListPoint[idCurrent].m_orthoAxeNext = itListPoint[idCurrent].m_miterAxe;
			} else {
				Log.todo("Unsupported type of point ....");
			}
		}
		// create segment list:
		bool haveStartLine = false;
		Vector2f leftPoint(0,0);
		Vector2f rightPoint(0,0);
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
								Vector2f left  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								Vector2f right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								// Check the miter limit:
								float limitRight = (left - it.m_pos).length() / _width * 2.0f;
								float limitLeft  = (right - it.m_pos).length() / _width * 2.0f;
								Log.verbose("    miter Limit: " << limitRight << " " << limitLeft << " <= " << _miterLimit);
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
								Vector2f axePrevious = (it.m_pos-it.m_posPrevious).safeNormalize();
								Vector2f axeNext = (it.m_posNext - it.m_pos).safeNormalize();
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
					Log.error("Start list point with a join, but last lement is not a join");
				}
			}
		}
		for (auto &it : itListPoint) {
			switch (it.m_type) {
				case esvg::render::Point::type::single:
					// just do nothing ....
					Log.verbose("Find Single " << it.m_pos);
					break;
				case esvg::render::Point::type::start:
					Log.verbose("Find Start " << it.m_pos);
					if (haveStartLine == true) {
						// close previous :
						Log.warning(" find a non close path ...");
						addSegment(leftPoint, rightPoint);
					}
					haveStartLine = true;
					startStopPoint(leftPoint, rightPoint, it, _cap, _width, true);
					break;
				case esvg::render::Point::type::stop:
					Log.verbose("Find Stop " << it.m_pos);
					if (haveStartLine == false) {
						Log.warning("find close path without start part ...");
						break;
					}
					haveStartLine = false;
					startStopPoint(leftPoint, rightPoint, it, _cap, _width, false);
					break;
				case esvg::render::Point::type::interpolation:
					{
						Log.verbose("Find interpolation " << it.m_pos);
						Vector2f left  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
						Vector2f right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
						//Draw from previous point:
						addSegment(leftPoint, left);
						Log.verbose("    segment :" << leftPoint << " -> " << left);
						addSegment(right, rightPoint);
						Log.verbose("    segment :" << right << " -> " << rightPoint);
						leftPoint = left;
						rightPoint = right;
					}
					break;
				case esvg::render::Point::type::join:
					Log.verbose("Find join " << it.m_pos);
					switch (_join) {
						case esvg::join_miter:
							{
								Vector2f left  = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								Vector2f right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
								// Check the miter limit:
								float limitRight = (left - it.m_pos).length() / _width * 2.0f;
								float limitLeft  = (right - it.m_pos).length() / _width * 2.0f;
								Log.verbose("    miter Limit: " << limitRight << " " << limitLeft << " <= " << _miterLimit);
								if (    limitRight <= _miterLimit
								     && limitLeft <= _miterLimit) {
									//Draw from previous point:
									addSegment(leftPoint, left);
									Log.verbose("    segment :" << leftPoint << " -> " << left);
									addSegment(right, rightPoint);
									Log.verbose("    segment :" << right << " -> " << rightPoint);
									leftPoint = left;
									rightPoint = right;
									break;
								} else {
									// We do a bevel join ...
									Log.verbose("    Find miter Limit ... ==> create BEVEL");
								}
							}
						case esvg::join_round:
						case esvg::join_bevel:
							{
								Vector2f axePrevious = (it.m_pos-it.m_posPrevious).safeNormalize();
								Vector2f axeNext = (it.m_posNext - it.m_pos).safeNormalize();
								float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									Vector2f right = getIntersect(rightPoint, it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
									Vector2f left1 =   it.m_pos
									             + it.m_orthoAxePrevious*_width*0.5f;
									Vector2f left2 =   it.m_pos
									             + it.m_orthoAxeNext*_width*0.5f;
									//Draw from previous point:
									addSegment(leftPoint, left1);
									Log.verbose("    segment :" << leftPoint << " -> " << left1);
									if (_join != esvg::join_round) {
										// Miter and bevel:
										addSegment(left1, left2);
										Log.verbose("    segment :" << left1 << " -> " << left2);
									}else {
										createSegmentListStroke(left1,
										                        left2,
										                        it.m_pos,
										                        _width,
										                        false);
									}
									addSegment(right, rightPoint);
									Log.verbose("    segment :" << right << " -> " << rightPoint);
									leftPoint = left2;
									rightPoint = right;
								} else {
									Vector2f left   = getIntersect(leftPoint,  it.m_pos-it.m_posPrevious, it.m_pos, it.m_miterAxe);
									Vector2f right1 =   it.m_pos
									              - it.m_orthoAxePrevious*_width*0.5f;
									Vector2f right2 =   it.m_pos
									              - it.m_orthoAxeNext*_width*0.5f;//Draw from previous point:
									addSegment(leftPoint, left);
									Log.verbose("    segment :" << leftPoint << " -> " << left);
									addSegment(right1, rightPoint);
									Log.verbose("    segment :" << right1 << " -> " << rightPoint);
									if (_join != esvg::join_round) {
										// Miter and bevel:
										addSegment(right2, right1);
										Log.verbose("    segment :" << right2 << " -> " << right1);
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

void esvg::render::SegmentList::startStopPoint(Vector2f& _leftPoint,
                                               Vector2f& _rightPoint,
                                               const esvg::render::Point& _point,
                                               enum esvg::cap _cap,
                                               float _width,
                                               bool _isStart) {
	switch (_cap) {
		case esvg::cap_butt:
			{
				Vector2f left =   _point.m_pos
				            + _point.m_miterAxe*_width*0.5f;
				Vector2f right =   _point.m_pos
				             - _point.m_miterAxe*_width*0.5f;
				if (_isStart == false) {
					//Draw from previous point:
					addSegment(_leftPoint, left);
					Log.verbose("    segment :" << _leftPoint << " -> " << left);
					addSegment(right, _rightPoint);
					Log.verbose("    segment :" << right << " -> " << _rightPoint);
				}
				_leftPoint = left;
				_rightPoint = right;
			}
			if (_isStart == false) {
				addSegment(_leftPoint, _rightPoint);
				Log.verbose("    segment :" << _leftPoint << " -> " << _rightPoint);
			} else {
				addSegment(_rightPoint, _leftPoint);
				Log.verbose("    segment :" << _rightPoint << " -> " << _leftPoint);
			}
			break;
		case esvg::cap_round:
			{
				if (_isStart == false) {
					Vector2f left =   _point.m_pos
					            + _point.m_miterAxe*_width*0.5f;
					Vector2f right =   _point.m_pos
					             - _point.m_miterAxe*_width*0.5f;
					if (_isStart == false) {
						//Draw from previous point:
						addSegment(_leftPoint, left);
						Log.verbose("    segment :" << _leftPoint << " -> " << left);
						addSegment(right, _rightPoint);
						Log.verbose("    segment :" << right << " -> " << _rightPoint);
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
				Vector2f nextAxe;
				if (_isStart == true) {
					nextAxe = _point.m_posNext - _point.m_pos;
				} else {
					nextAxe = _point.m_posPrevious - _point.m_pos;
				}
				Vector2f left =   _point.m_pos
				            + _point.m_miterAxe*_width*0.5f;
				Vector2f right =   _point.m_pos
				             - _point.m_miterAxe*_width*0.5f;
				mat2x3 tmpMat = etk::mat2x3Translate(nextAxe.safeNormalize()*_width*-0.5f);
				left = tmpMat*left;
				right = tmpMat*right;
				if (_isStart == false) {
					if (_isStart == false) {
						//Draw from previous point:
						addSegment(_leftPoint, left);
						Log.verbose("    segment :" << _leftPoint << " -> " << left);
						addSegment(right, _rightPoint);
						Log.verbose("    segment :" << right << " -> " << _rightPoint);
					}
				}
				_leftPoint = left;
				_rightPoint = right;
				if (_isStart == false) {
					addSegment(_leftPoint, _rightPoint);
					Log.verbose("    segment :" << _leftPoint << " -> " << _rightPoint);
				} else {
					addSegment(_rightPoint, _leftPoint);
					Log.verbose("    segment :" << _rightPoint << " -> " << _leftPoint);
				}
				Log.verbose("    segment :" << _leftPoint << " -> " << _rightPoint);
			}
			break;
		default:
			Log.error(" Undefined CAP TYPE");
			break;
	}
}

void esvg::render::SegmentList::applyMatrix(const mat2x3& _transformationMatrix) {
	for (auto &it : m_data) {
		it.applyMatrix(_transformationMatrix);
	}
}


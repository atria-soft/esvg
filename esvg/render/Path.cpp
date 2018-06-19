/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <esvg/debug.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Element.hpp>

void esvg::render::Path::clear() {
	m_listElement.clear();
}

void esvg::render::Path::stop() {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementStop>());
}

void esvg::render::Path::close(bool _relative) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementClose>(_relative));
}

void esvg::render::Path::moveTo(bool _relative, const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementMoveTo>(_relative, _pos));
}

void esvg::render::Path::lineTo(bool _relative, const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementLineTo>(_relative, _pos));
}

void esvg::render::Path::lineToH(bool _relative, float _posX) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementLineToH>(_relative, _posX));
}

void esvg::render::Path::lineToV(bool _relative, float _posY) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementLineToV>(_relative, _posY));
}

void esvg::render::Path::curveTo(bool _relative, const vec2& _pos1, const vec2& _pos2, const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementCurveTo>(_relative, _pos1, _pos2, _pos));
}

void esvg::render::Path::smoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementSmoothCurveTo>(_relative, _pos2, _pos));
}

void esvg::render::Path::bezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementBezierCurveTo>(_relative, _pos1, _pos));
}

void esvg::render::Path::bezierSmoothCurveTo(bool _relative, const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementBezierSmoothCurveTo>(_relative, _pos));
}

void esvg::render::Path::ellipticTo(bool _relative,
                                    const vec2& _radius,
                                    float _angle,
                                    bool _largeArcFlag,
                                    bool _sweepFlag,
                                    const vec2& _pos) {
	m_listElement.pushBack(ememory::makeShared<esvg::render::ElementElliptic>(_relative, _radius, _angle, _largeArcFlag, _sweepFlag, _pos));
}

static const char* spacingDist(int32_t _spacing) {
	static const char *tmpValue = "                                                                                ";
	if (_spacing>20) {
		_spacing = 20;
	}
	return tmpValue + 20*4 - _spacing*4;
}

void esvg::render::Path::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Path");
	for(auto &it : m_listElement) {
		if (it == null) {
			continue;
		}
		ESVG_DEBUG(spacingDist(_spacing+1) << *it);
	}
}


void interpolateCubicBezier(etk::Vector<esvg::render::Point>& _listPoint,
                            int32_t _recurtionMax,
                            float _threshold,
                            vec2 _pos1,
                            vec2 _pos2,
                            vec2 _pos3,
                            vec2 _pos4,
                            int32_t _level,
                            enum esvg::render::Point::type _type) {
	if (_level > _recurtionMax) {
		return;
	}
	vec2 pos12 = (_pos1+_pos2)*0.5f;
	vec2 pos23 = (_pos2+_pos3)*0.5f;
	vec2 pos34 = (_pos3+_pos4)*0.5f;
	
	vec2 delta = _pos4 - _pos1;
	#ifndef __STDCPP_LLVM__
		float distance2 = etk::abs(((_pos2.x() - _pos4.x()) * delta.y() - (_pos2.y() - _pos4.y()) * delta.x() ));
		float distance3 = etk::abs(((_pos3.x() - _pos4.x()) * delta.y() - (_pos3.y() - _pos4.y()) * delta.x() ));
	#else
		float distance2 = fabs(((_pos2.x() - _pos4.x()) * delta.y() - (_pos2.y() - _pos4.y()) * delta.x() ));
		float distance3 = fabs(((_pos3.x() - _pos4.x()) * delta.y() - (_pos3.y() - _pos4.y()) * delta.x() ));
	#endif
	
	if ((distance2 + distance3)*(distance2 + distance3) < _threshold * delta.length2()) {
		_listPoint.pushBack(esvg::render::Point(_pos4, _type) );
		return;
	}
	vec2 pos123 = (pos12+pos23)*0.5f;
	vec2 pos234 = (pos23+pos34)*0.5f;
	vec2 pos1234 = (pos123+pos234)*0.5f;
	
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, _pos1, pos12, pos123, pos1234, _level+1, esvg::render::Point::type::interpolation);
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, pos1234, pos234, pos34, _pos4, _level+1, _type);
}

static float vectorAngle(vec2 _uuu, vec2 _vvv) {
	_uuu.safeNormalize();
	_vvv.safeNormalize();
	return atan2(_uuu.cross(_vvv), _uuu.dot(_vvv));
}

esvg::render::PointList esvg::render::Path::generateListPoints(int32_t _level, int32_t _recurtionMax, float _threshold) {
	ESVG_VERBOSE(spacingDist(_level) << "Generate List Points ... from a path");
	esvg::render::PointList out;
	etk::Vector<esvg::render::Point> tmpListPoint;
	vec2 lastPosition(0.0f, 0.0f);
	vec2 lastAngle(0.0f, 0.0f);
	int32_t lastPointId = -1;
	bool PathStart = false;
	// Foreach element, we move in the path:
	for(auto &it : m_listElement) {
		if (it == null) {
			continue;
		}
		ESVG_VERBOSE(spacingDist(_level+1) << " Draw : " << *it);
		switch (it->getType()) {
			case esvg::render::path_stop:
				if (tmpListPoint.size() != 0) {
					if (tmpListPoint.size() == 0) {
						ESVG_WARNING(spacingDist(_level+1) << " Request path stop of not starting path ...");
					} else {
						tmpListPoint.back().setEndPath();
						out.addList(tmpListPoint);
						tmpListPoint.clear();
					}
				}
				lastAngle = vec2(0.0f, 0.0f);
				// nothing alse to do ...
				break;
			case esvg::render::path_close:
				if (tmpListPoint.size() != 0) {
					if (tmpListPoint.size() == 0) {
						ESVG_WARNING(spacingDist(_level+1) << " Request path close of not starting path ...");
					} else {
						// find the previous tart of the path ...
						tmpListPoint.front().m_type = esvg::render::Point::type::join;
						// Remove the last point if it is the same position...
						vec2 delta = (tmpListPoint.front().m_pos - tmpListPoint.back().m_pos).absolute();
						if (    delta.x() <= 0.00001
						     && delta.y() <= 0.00001) {
							tmpListPoint.popBack();
							ESVG_VERBOSE("        Remove point Z property : " << tmpListPoint.back().m_pos << " with delta=" << delta);
						}
						out.addList(tmpListPoint);
						tmpListPoint.clear();
					}
				}
				lastAngle = vec2(0.0f, 0.0f);
				// nothing alse to do ...
				break;
			case esvg::render::path_moveTo:
				// stop last path
				if (tmpListPoint.size() != 0) {
					tmpListPoint.back().setEndPath();
					out.addList(tmpListPoint);
					tmpListPoint.clear();
				}
				// create a new one
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::start));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_lineTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::start));
				}
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_lineToH:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::start));
				}
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_lineToV:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::start));
				}
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_curveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				}
				{
					vec2 lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos1 = lastPosition + it->getPos1();
					vec2 pos2 = lastPosition + it->getPos2();
					vec2 pos = lastPosition + it->getPos();
					interpolateCubicBezier(tmpListPoint,
					                       _recurtionMax,
					                       _threshold,
					                       lastPosStore,
					                       pos1,
					                       pos2,
					                       pos,
					                       0,
					                       esvg::render::Point::type::join);
					lastPosition = pos;
					lastAngle = pos2;
				}
				break;
			case esvg::render::path_smoothCurveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				}
				{
					vec2 lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos2 = lastPosition + it->getPos2();
					vec2 pos = lastPosition + it->getPos();
					// generate Pos 1
					vec2 pos1 = lastPosStore*2.0f - lastAngle;
					interpolateCubicBezier(tmpListPoint,
					                       _recurtionMax,
					                       _threshold,
					                       lastPosStore,
					                       pos1,
					                       pos2,
					                       pos,
					                       0,
					                       esvg::render::Point::type::join);
					lastPosition = pos;
					lastAngle = pos2;
				}
				break;
			case esvg::render::path_bezierCurveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				}
				{
					vec2 lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos = lastPosition + it->getPos();
					vec2 tmp1 = lastPosition + it->getPos1();
					// generate pos1 and pos2
					vec2 pos1 = lastPosStore + (tmp1 - lastPosStore)*0.666666666f;
					vec2 pos2 = pos          + (tmp1 - pos)*0.666666666f;
					interpolateCubicBezier(tmpListPoint,
					                       _recurtionMax,
					                       _threshold,
					                       lastPosStore,
					                       pos1,
					                       pos2,
					                       pos,
					                       0,
					                       esvg::render::Point::type::join);
					lastPosition = pos;
					lastAngle = tmp1;
				}
				break;
			case esvg::render::path_bezierSmoothCurveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				}
				{
					vec2 lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos = lastPosition + it->getPos();
					vec2 tmp1 = lastPosStore*2.0f - lastAngle;
					// generate pos1 and pos2
					vec2 pos1 = lastPosStore + (tmp1 - lastPosStore)*0.666666666f;
					vec2 pos2 = pos          + (tmp1 - pos)*0.66666666f;
					interpolateCubicBezier(tmpListPoint,
					                       _recurtionMax,
					                       _threshold,
					                       lastPosStore,
					                       pos1,
					                       pos2,
					                       pos,
					                       0,
					                       esvg::render::Point::type::join);
					lastPosition = pos;
					lastAngle = tmp1;
				}
				break;
			case esvg::render::path_elliptic:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
				}
				{
					ememory::SharedPtr<esvg::render::ElementElliptic> tmpIt(ememory::dynamicPointerCast<esvg::render::ElementElliptic>(it));
					float angle = tmpIt->m_angle * (M_PI / 180.0);
					ESVG_TODO(spacingDist(_level+1) << " Elliptic arc: radius=" << tmpIt->getPos1());
					ESVG_TODO(spacingDist(_level+1) << "               angle=" << tmpIt->m_angle);
					ESVG_TODO(spacingDist(_level+1) << "               m_largeArcFlag=" << tmpIt->m_largeArcFlag);
					ESVG_TODO(spacingDist(_level+1) << "               m_sweepFlag=" << tmpIt->m_sweepFlag);
					
					
					vec2 lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos = lastPosition + it->getPos();
					float rotationX = tmpIt->m_angle * (M_PI / 180.0);
					vec2 radius = tmpIt->getPos1();
					
					#ifdef DEBUG
						m_debugInformation.addSegment(lastPosStore, pos);
					#endif
					vec2 delta = lastPosStore - pos;
					float ddd = delta.length();
					if (    ddd < 1e-6f
					     || radius.x() < 1e-6f
					     || radius.y() < 1e-6f) {
						ESVG_WARNING("Degenerate arc in Line");
						if (tmpListPoint.size() == 0) {
							tmpListPoint.pushBack(esvg::render::Point(lastPosition, esvg::render::Point::type::join));
						}
						tmpListPoint.pushBack(esvg::render::Point(pos, esvg::render::Point::type::join));
					} else {
						// Convert to center point parameterization.
						// http://www.w3.org/TR/SVG11/implnote.html#ArcImplementationNotes
						// procedure describe here : http://www.w3.org/TR/SVG11/implnote.html#ArcConversionCenterToEndpoint
						// Compute delta'
						mat2x3 matrixRotationCenter = etk::mat2x3Rotate(-rotationX);
						vec2 deltaPrim = matrixRotationCenter * (delta*0.5f);
						ddd =   (deltaPrim.x()*deltaPrim.x())/(radius.x()*radius.x())
						      + (deltaPrim.y()*deltaPrim.y())/(radius.y()*radius.y());
						if (ddd > 1.0f) {
							#ifndef __STDCPP_LLVM__
								ddd = etk::sqrt(ddd);
							#else
								ddd = sqrtf(ddd);
							#endif
							radius *= ddd;
						}
						// Compute center'
						float sss = 0.0f;
						float ssa =   radius.x()*radius.x()*radius.y()*radius.y()
						            - radius.x()*radius.x()*deltaPrim.y()*deltaPrim.y()
						            - radius.y()*radius.y()*deltaPrim.x()*deltaPrim.x();
						float ssb =   radius.x()*radius.x()*deltaPrim.y()*deltaPrim.y()
						            + radius.y()*radius.y()*deltaPrim.x()*deltaPrim.x();
						if (ssa < 0.0f) {
							ssa = 0.0f;
						}
						if (ssb > 0.0f) {
							#ifndef __STDCPP_LLVM__
								sss = etk::sqrt(ssa / ssb);
							#else
								sss = sqrtf(ssa / ssb);
							#endif
						}
						if (tmpIt->m_largeArcFlag == tmpIt->m_sweepFlag) {
							sss *= -1.0f;
						}
						vec2 centerPrime(sss * radius.x() * deltaPrim.y() / radius.y(),
						                 sss * -radius.y() * deltaPrim.x() / radius.x());
						// Compute center from center'
						mat2x3 matrix = etk::mat2x3Rotate(rotationX);
						vec2 center = (lastPosStore + pos)*0.5f + matrix*centerPrime;
						#ifdef DEBUG
							m_debugInformation.addSegment(center-vec2(3.0,3.0), center+vec2(3.0,3.0));
							m_debugInformation.addSegment(center-vec2(3.0,-3.0), center+vec2(3.0,-3.0));
						#endif
						// Calculate theta1, and delta theta.
						vec2 vectorA = (deltaPrim - centerPrime) / radius;
						vec2 vectorB = (deltaPrim + centerPrime) / radius * -1.0f;
						#ifdef DEBUG
							m_debugInformation.addSegment(center, center+vectorA*radius.x());
							m_debugInformation.addSegment(center, center+vectorB*radius.y());
						#endif
						// Initial angle
						float theta1 = vectorAngle(vec2(1.0f,0.0f), vectorA);
						// Delta angle
						float deltaTheta = vectorAngle(vectorA, vectorB);
						// special case of invert angle...
						if (    (    deltaTheta == float(M_PI)
						          || deltaTheta == -float(M_PI))
						     && tmpIt->m_sweepFlag == false) {
							deltaTheta *= -1.0f;
						}
						if (tmpIt->m_largeArcFlag == true) {
							// Choose large arc
							if (deltaTheta > 0.0f) {
								deltaTheta -= 2.0f*M_PI;
							} else {
								deltaTheta += 2.0f*M_PI;
							}
						}
						// Approximate the arc using cubic spline segments.
						matrix.translate(center);
						// Split arc into max 90 degree segments.
						// The loop assumes an iteration per end point (including start and end), this +1.
						#ifndef __STDCPP_LLVM__
							int32_t ndivs = int32_t(etk::abs(deltaTheta) / (M_PI*0.5f)) + 1;
						#else
							int32_t ndivs = int32_t(fabs(deltaTheta) / (M_PI*0.5f)) + 1;
						#endif
						float hda = (deltaTheta / float(ndivs)) * 0.5f;
						#ifndef __STDCPP_LLVM__
							float kappa = etk::abs(4.0f / 3.0f * (1.0f - etk::cos(hda)) / etk::sin(hda));
						#else
							float kappa = fabs(4.0f / 3.0f * (1.0f - cosf(hda)) / sinf(hda));
						#endif
						if (deltaTheta < 0.0f) {
							kappa = -kappa;
						}
						vec2 pointPosPrevious(0.0,0.0);
						vec2 tangentPrevious(0.0,0.0);
						for (int32_t iii=0; iii<=ndivs; ++iii) {
							float a = theta1 + deltaTheta * (float(iii)/(float)ndivs);
							#ifndef __STDCPP_LLVM__
								delta = vec2(etk::cos(a), etk::sin(a));
							#else
								delta = vec2(cosf(a), sinf(a));
							#endif
							// position
							vec2 pointPos = matrix * vec2(delta.x()*radius.x(), delta.y()*radius.y());
							// tangent
							vec2 tangent = matrix.applyScaleRotation(vec2(-delta.y()*radius.x() * kappa, delta.x()*radius.y() * kappa));
							if (iii > 0) {
								vec2 zlastPosStore(lastPosition);
								if (it->getRelative() == false) {
									lastPosition = vec2(0.0f, 0.0f);
								}
								vec2 zpos1 = pointPosPrevious + tangentPrevious;
								vec2 zpos2 = pointPos - tangent;
								vec2 zpos = pointPos;
								interpolateCubicBezier(tmpListPoint,
								                       _recurtionMax,
								                       _threshold,
								                       zlastPosStore,
								                       zpos1,
								                       zpos2,
								                       zpos,
								                       0,
								                       esvg::render::Point::type::join);
								lastPosition = zpos;
								lastAngle = zpos2;
							}
							pointPosPrevious = pointPos;
							tangentPrevious = tangent;
						}
					}
					lastPosition = pos;
				}
				break;
			default:
				ESVG_ERROR(spacingDist(_level+1) << " Unknow PATH commant (internal error)");
				break;
		}
	}
	// special case : No request end of path ==> open path:
	if (tmpListPoint.size() != 0) {
		ESVG_VERBOSE("Auto-end PATH");
		tmpListPoint.back().setEndPath();
		out.addList(tmpListPoint);
		tmpListPoint.clear();
	}
	out.display();
	return out;
}


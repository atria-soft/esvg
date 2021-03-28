/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <esvg/debug.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Element.hpp>

void esvg::render::Path::clear() {
	this.listElement.clear();
}

void esvg::render::Path::stop() {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementStop>());
}

void esvg::render::Path::close(boolean _relative) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementClose>(_relative));
}

void esvg::render::Path::moveTo(boolean _relative, const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementMoveTo>(_relative, _pos));
}

void esvg::render::Path::lineTo(boolean _relative, const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementLineTo>(_relative, _pos));
}

void esvg::render::Path::lineToH(boolean _relative, float _posX) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementLineToH>(_relative, _posX));
}

void esvg::render::Path::lineToV(boolean _relative, float _posY) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementLineToV>(_relative, _posY));
}

void esvg::render::Path::curveTo(boolean _relative, const Vector2f& _pos1, const Vector2f& _pos2, const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementCurveTo>(_relative, _pos1, _pos2, _pos));
}

void esvg::render::Path::smoothCurveTo(boolean _relative, const Vector2f& _pos2, const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementSmoothCurveTo>(_relative, _pos2, _pos));
}

void esvg::render::Path::bezierCurveTo(boolean _relative, const Vector2f& _pos1, const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementBezierCurveTo>(_relative, _pos1, _pos));
}

void esvg::render::Path::bezierSmoothCurveTo(boolean _relative, const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementBezierSmoothCurveTo>(_relative, _pos));
}

void esvg::render::Path::ellipticTo(boolean _relative,
                                    const Vector2f& _radius,
                                    float _angle,
                                    boolean _largeArcFlag,
                                    boolean _sweepFlag,
                                    const Vector2f& _pos) {
	this.listElement.pushBack(ememory::makeShared<esvg::render::ElementElliptic>(_relative, _radius, _angle, _largeArcFlag, _sweepFlag, _pos));
}

static const char* spacingDist(int _spacing) {
	static const char *tmpValue = "                                                                                ";
	if (_spacing>20) {
		_spacing = 20;
	}
	return tmpValue + 20*4 - _spacing*4;
}

void esvg::render::Path::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Path");
	for(auto &it : this.listElement) {
		if (it == null) {
			continue;
		}
		Log.debug(spacingDist(_spacing+1) << *it);
	}
}


void interpolateCubicBezier(List<esvg::render::Point>& _listPoint,
                            int _recurtionMax,
                            float _threshold,
                            Vector2f _pos1,
                            Vector2f _pos2,
                            Vector2f _pos3,
                            Vector2f _pos4,
                            int _level,
                            enum esvg::render::Point::type _type) {
	if (_level > _recurtionMax) {
		return;
	}
	Vector2f pos12 = (_pos1+_pos2)*0.5f;
	Vector2f pos23 = (_pos2+_pos3)*0.5f;
	Vector2f pos34 = (_pos3+_pos4)*0.5f;
	
	Vector2f delta = _pos4 - _pos1;
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
	Vector2f pos123 = (pos12+pos23)*0.5f;
	Vector2f pos234 = (pos23+pos34)*0.5f;
	Vector2f pos1234 = (pos123+pos234)*0.5f;
	
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, _pos1, pos12, pos123, pos1234, _level+1, esvg::render::Point::type::interpolation);
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, pos1234, pos234, pos34, _pos4, _level+1, _type);
}

static float vectorAngle(Vector2f _uuu, Vector2f _vvv) {
	_uuu.safeNormalize();
	_vvv.safeNormalize();
	return atan2(_uuu.cross(_vvv), _uuu.dot(_vvv));
}

esvg::render::PointList esvg::render::Path::generateListPoints(int _level, int _recurtionMax, float _threshold) {
	Log.verbose(spacingDist(_level) << "Generate List Points ... from a path");
	esvg::render::PointList out;
	List<esvg::render::Point> tmpListPoint;
	Vector2f lastPosition(0.0f, 0.0f);
	Vector2f lastAngle(0.0f, 0.0f);
	int lastPointId = -1;
	boolean PathStart = false;
	// Foreach element, we move in the path:
	for(auto &it : this.listElement) {
		if (it == null) {
			continue;
		}
		Log.verbose(spacingDist(_level+1) << " Draw : " << *it);
		switch (it->getType()) {
			case esvg::render::path_stop:
				if (tmpListPoint.size() != 0) {
					if (tmpListPoint.size() == 0) {
						Log.warning(spacingDist(_level+1) << " Request path stop of not starting path ...");
					} else {
						tmpListPoint.back().setEndPath();
						out.addList(tmpListPoint);
						tmpListPoint.clear();
					}
				}
				lastAngle = Vector2f(0.0f, 0.0f);
				// nothing alse to do ...
				break;
			case esvg::render::path_close:
				if (tmpListPoint.size() != 0) {
					if (tmpListPoint.size() == 0) {
						Log.warning(spacingDist(_level+1) << " Request path close of not starting path ...");
					} else {
						// find the previous tart of the path ...
						tmpListPoint.front().this.type = esvg::render::Point::type::join;
						// Remove the last point if it is the same position...
						Vector2f delta = (tmpListPoint.front().this.pos - tmpListPoint.back().this.pos).absolute();
						if (    delta.x() <= 0.00001
						     && delta.y() <= 0.00001) {
							tmpListPoint.popBack();
							Log.verbose("        Remove point Z property : " << tmpListPoint.back().this.pos << " with delta=" << delta);
						}
						out.addList(tmpListPoint);
						tmpListPoint.clear();
					}
				}
				lastAngle = Vector2f(0.0f, 0.0f);
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
					lastPosition = Vector2f(0.0f, 0.0f);
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
					lastPosition = Vector2f(0.0f, 0.0f);
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
					lastPosition = Vector2f(0.0f, 0.0f);
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
					lastPosition = Vector2f(0.0f, 0.0f);
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
					Vector2f lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = Vector2f(0.0f, 0.0f);
					}
					Vector2f pos1 = lastPosition + it->getPos1();
					Vector2f pos2 = lastPosition + it->getPos2();
					Vector2f pos = lastPosition + it->getPos();
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
					Vector2f lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = Vector2f(0.0f, 0.0f);
					}
					Vector2f pos2 = lastPosition + it->getPos2();
					Vector2f pos = lastPosition + it->getPos();
					// generate Pos 1
					Vector2f pos1 = lastPosStore*2.0f - lastAngle;
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
					Vector2f lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = Vector2f(0.0f, 0.0f);
					}
					Vector2f pos = lastPosition + it->getPos();
					Vector2f tmp1 = lastPosition + it->getPos1();
					// generate pos1 and pos2
					Vector2f pos1 = lastPosStore + (tmp1 - lastPosStore)*0.666666666f;
					Vector2f pos2 = pos          + (tmp1 - pos)*0.666666666f;
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
					Vector2f lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = Vector2f(0.0f, 0.0f);
					}
					Vector2f pos = lastPosition + it->getPos();
					Vector2f tmp1 = lastPosStore*2.0f - lastAngle;
					// generate pos1 and pos2
					Vector2f pos1 = lastPosStore + (tmp1 - lastPosStore)*0.666666666f;
					Vector2f pos2 = pos          + (tmp1 - pos)*0.66666666f;
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
					float angle = tmpIt->this.angle * (M_PI / 180.0);
					Log.todo(spacingDist(_level+1) << " Elliptic arc: radius=" << tmpIt->getPos1());
					Log.todo(spacingDist(_level+1) << "               angle=" << tmpIt->this.angle);
					Log.todo(spacingDist(_level+1) << "               this.largeArcFlag=" << tmpIt->this.largeArcFlag);
					Log.todo(spacingDist(_level+1) << "               this.sweepFlag=" << tmpIt->this.sweepFlag);
					
					
					Vector2f lastPosStore(lastPosition);
					if (it->getRelative() == false) {
						lastPosition = Vector2f(0.0f, 0.0f);
					}
					Vector2f pos = lastPosition + it->getPos();
					float rotationX = tmpIt->this.angle * (M_PI / 180.0);
					Vector2f radius = tmpIt->getPos1();
					
					#ifdef DEBUG
						this.debugInformation.addSegment(lastPosStore, pos);
					#endif
					Vector2f delta = lastPosStore - pos;
					float ddd = delta.length();
					if (    ddd < 1e-6f
					     || radius.x() < 1e-6f
					     || radius.y() < 1e-6f) {
						Log.warning("Degenerate arc in Line");
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
						Vector2f deltaPrim = matrixRotationCenter * (delta*0.5f);
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
						if (tmpIt->this.largeArcFlag == tmpIt->this.sweepFlag) {
							sss *= -1.0f;
						}
						Vector2f centerPrime(sss * radius.x() * deltaPrim.y() / radius.y(),
						                 sss * -radius.y() * deltaPrim.x() / radius.x());
						// Compute center from center'
						mat2x3 matrix = etk::mat2x3Rotate(rotationX);
						Vector2f center = (lastPosStore + pos)*0.5f + matrix*centerPrime;
						#ifdef DEBUG
							this.debugInformation.addSegment(center-Vector2f(3.0,3.0), center+Vector2f(3.0,3.0));
							this.debugInformation.addSegment(center-Vector2f(3.0,-3.0), center+Vector2f(3.0,-3.0));
						#endif
						// Calculate theta1, and delta theta.
						Vector2f vectorA = (deltaPrim - centerPrime) / radius;
						Vector2f vectorB = (deltaPrim + centerPrime) / radius * -1.0f;
						#ifdef DEBUG
							this.debugInformation.addSegment(center, center+vectorA*radius.x());
							this.debugInformation.addSegment(center, center+vectorB*radius.y());
						#endif
						// Initial angle
						float theta1 = vectorAngle(Vector2f(1.0f,0.0f), vectorA);
						// Delta angle
						float deltaTheta = vectorAngle(vectorA, vectorB);
						// special case of invert angle...
						if (    (    deltaTheta == float(M_PI)
						          || deltaTheta == -float(M_PI))
						     && tmpIt->this.sweepFlag == false) {
							deltaTheta *= -1.0f;
						}
						if (tmpIt->this.largeArcFlag == true) {
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
							int ndivs = int(etk::abs(deltaTheta) / (M_PI*0.5f)) + 1;
						#else
							int ndivs = int(fabs(deltaTheta) / (M_PI*0.5f)) + 1;
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
						Vector2f pointPosPrevious(0.0,0.0);
						Vector2f tangentPrevious(0.0,0.0);
						for (int iii=0; iii<=ndivs; ++iii) {
							float a = theta1 + deltaTheta * (float(iii)/(float)ndivs);
							#ifndef __STDCPP_LLVM__
								delta = Vector2f(etk::cos(a), etk::sin(a));
							#else
								delta = Vector2f(cosf(a), sinf(a));
							#endif
							// position
							Vector2f pointPos = matrix * Vector2f(delta.x()*radius.x(), delta.y()*radius.y());
							// tangent
							Vector2f tangent = matrix.applyScaleRotation(Vector2f(-delta.y()*radius.x() * kappa, delta.x()*radius.y() * kappa));
							if (iii > 0) {
								Vector2f zlastPosStore(lastPosition);
								if (it->getRelative() == false) {
									lastPosition = Vector2f(0.0f, 0.0f);
								}
								Vector2f zpos1 = pointPosPrevious + tangentPrevious;
								Vector2f zpos2 = pointPos - tangent;
								Vector2f zpos = pointPos;
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
				Log.error(spacingDist(_level+1) << " Unknow PATH commant (internal error)");
				break;
		}
	}
	// special case : No request end of path ==> open path:
	if (tmpListPoint.size() != 0) {
		Log.verbose("Auto-end PATH");
		tmpListPoint.back().setEndPath();
		out.addList(tmpListPoint);
		tmpListPoint.clear();
	}
	out.display();
	return out;
}


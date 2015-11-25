/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <esvg/debug.h>
#include <esvg/render/Path.h>
#include <esvg/render/Element.h>

#undef __class__
#define __class__	"rerder::Path"

void esvg::render::Path::clear() {
	m_listElement.clear();
}

void esvg::render::Path::stop() {
	m_listElement.push_back(std::make_shared<esvg::render::ElementStop>());
}

void esvg::render::Path::close(bool _relative) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementClose>(_relative));
}

void esvg::render::Path::moveTo(bool _relative, const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementMoveTo>(_relative, _pos));
}

void esvg::render::Path::lineTo(bool _relative, const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementLineTo>(_relative, _pos));
}

void esvg::render::Path::lineToH(bool _relative, float _posX) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementLineToH>(_relative, _posX));
}

void esvg::render::Path::lineToV(bool _relative, float _posY) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementLineToV>(_relative, _posY));
}

void esvg::render::Path::curveTo(bool _relative, const vec2& _pos1, const vec2& _pos2, const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementCurveTo>(_relative, _pos1, _pos2, _pos));
}

void esvg::render::Path::smoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementSmoothCurveTo>(_relative, _pos2, _pos));
}

void esvg::render::Path::bezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementBezierCurveTo>(_relative, _pos1, _pos));
}

void esvg::render::Path::bezierSmoothCurveTo(bool _relative, const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementBezierSmoothCurveTo>(_relative, _pos));
}

void esvg::render::Path::ellipticTo(bool _relative,
                                    const vec2& _radius,
                                    float _angle,
                                    bool _largeArcFlag,
                                    bool _sweepFlag,
                                    const vec2& _pos) {
	m_listElement.push_back(std::make_shared<esvg::render::ElementElliptic>(_relative, _radius, _angle, _largeArcFlag, _sweepFlag, _pos));
}

static const char* spacingDist(int32_t _spacing) {
	static const char *tmpValue = "                                                                                ";
	if (_spacing>20) {
		_spacing = 20;
	}
	return tmpValue + 20*4 - _spacing*4;
}

void esvg::render::Path::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Path");
	for(auto &it : m_listElement) {
		if (it == nullptr) {
			continue;
		}
		SVG_DEBUG(spacingDist(_spacing+1) << *it);
	}
}


void interpolateCubicBezier(std::vector<esvg::render::Point>& _listPoint,
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
	float distance2 = std::abs(((_pos2.x() - _pos4.x()) * delta.y() - (_pos2.y() - _pos4.y()) * delta.x() ));
	float distance3 = std::abs(((_pos3.x() - _pos4.x()) * delta.y() - (_pos3.y() - _pos4.y()) * delta.x() ));
	
	if ((distance2 + distance3)*(distance2 + distance3) < _threshold * delta.length2()) {
		_listPoint.push_back(esvg::render::Point(_pos4, _type) );
		return;
	}
	vec2 pos123 = (pos12+pos23)*0.5f;
	vec2 pos234 = (pos23+pos34)*0.5f;
	vec2 pos1234 = (pos123+pos234)*0.5f;
	
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, _pos1, pos12, pos123, pos1234, _level+1, esvg::render::Point::type_interpolation);
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, pos1234, pos234, pos34, _pos4, _level+1, _type);
}

esvg::render::PointList esvg::render::Path::generateListPoints(int32_t _level, int32_t _recurtionMax, float _threshold) {
	SVG_VERBOSE(spacingDist(_level) << "Generate List Points ... from a path");
	esvg::render::PointList out;
	std::vector<esvg::render::Point> tmpListPoint;
	vec2 lastPosition(0.0f, 0.0f);
	vec2 lastAngle(0.0f, 0.0f);
	int32_t lastPointId = -1;
	bool PathStart = false;
	// Foreach element, we move in the path:
	for(auto &it : m_listElement) {
		if (it == nullptr) {
			continue;
		}
		SVG_VERBOSE(spacingDist(_level+1) << " Draw : " << *it);
		switch (it->getType()) {
			case esvg::render::path_stop:
				if (tmpListPoint.size() != 0) {
					if (tmpListPoint.size() == 0) {
						SVG_WARNING(spacingDist(_level+1) << " Request path stop of not starting path ...");
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
						SVG_WARNING(spacingDist(_level+1) << " Request path close of not starting path ...");
					} else {
						// find the previous tart of the path ...
						tmpListPoint.front().m_type = esvg::render::Point::type_join;
						// Remove the last point if it is the same position...
						if (tmpListPoint.front().m_pos == tmpListPoint.back().m_pos) {
							tmpListPoint.pop_back();
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
				tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_lineTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				}
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_lineToH:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				}
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_lineToV:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				}
				if (it->getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it->getPos();
				tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
				lastAngle = lastPosition;
				break;
			case esvg::render::path_curveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
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
					                       esvg::render::Point::type_join);
					lastPosition = pos;
					lastAngle = pos2;
				}
				break;
			case esvg::render::path_smoothCurveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
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
					                       esvg::render::Point::type_join);
					lastPosition = pos;
					lastAngle = pos2;
				}
				break;
			case esvg::render::path_bezierCurveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
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
					                       esvg::render::Point::type_join);
					lastPosition = pos;
					lastAngle = tmp1;
				}
				break;
			case esvg::render::path_bezierSmoothCurveTo:
				// If no previous point, we need to create the last point has start ...
				if (tmpListPoint.size() == 0) {
					tmpListPoint.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
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
					                       esvg::render::Point::type_join);
					lastPosition = pos;
					lastAngle = tmp1;
				}
				break;
			case esvg::render::path_elliptic:
				SVG_TODO(spacingDist(_level+1) << " Elliptic arc not supported now ...");
				/*
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : " << *it);
				path.ellipticTo(it->getRelative(),
				                it->m_element[0],
				                it->m_element[1],
				                it->m_element[2],
				                it->m_element[3],
				                it->m_element[4],
				                it->m_element[5],
				                it->m_element[6] );
				*/
				break;
			default:
				SVG_ERROR(spacingDist(_level+1) << " Unknow PATH commant (internal error)");
				break;
		}
	}
	if (tmpListPoint.size() != 0) {
		SVG_WARNING("TODO ... check this ...");
		out.addList(tmpListPoint);
		tmpListPoint.clear();
	}
	out.display();
	return out;
}
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

void esvg::render::Path::clear() {
	m_listElement.clear();
}

void esvg::render::Path::stop(bool _relative) {
	m_listElement.push_back(esvg::render::ElementStop(_relative));
}

void esvg::render::Path::moveTo(bool _relative, const vec2& _pos) {
	m_listElement.push_back(esvg::render::ElementMoveTo(_relative, _pos));
}

void esvg::render::Path::lineTo(bool _relative, const vec2& _pos) {
	m_listElement.push_back(esvg::render::ElementLineTo(_relative, _pos));
}

void esvg::render::Path::lineToH(bool _relative, float _posX) {
	m_listElement.push_back(esvg::render::ElementLineToH(_relative, _posX));
}

void esvg::render::Path::lineToV(bool _relative, float _posY) {
	m_listElement.push_back(esvg::render::ElementLineToV(_relative, _posY));
}

void esvg::render::Path::curveTo(bool _relative, const vec2& _pos1, const vec2& _pos2, const vec2& _pos) {
	m_listElement.push_back(esvg::render::ElementCurveTo(_relative, _pos1, _pos2, _pos));
}

void esvg::render::Path::smoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos) {
	m_listElement.push_back(esvg::render::ElementSmoothCurveTo(_relative, _pos2, _pos));
}

void esvg::render::Path::bezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos) {
	m_listElement.push_back(esvg::render::ElementBezierCurveTo(_relative, _pos1, _pos));
}

void esvg::render::Path::bezierSmoothCurveTo(bool _relative, const vec2& _pos) {
	m_listElement.push_back(esvg::render::ElementBezierSmoothCurveTo(_relative, _pos));
}

void esvg::render::Path::ellipticTo(bool _relative, float _val0, float _val1, float _val2, float _val3, float _val4, float _val5, float _val6) {
	m_listElement.push_back(esvg::render::ElementElliptic(_relative, _val0, _val1, _val2, _val3, _val4, _val5, _val6));
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
		switch (it.getType()) {
			case esvg::render::path_stop:
				SVG_DEBUG(spacingDist(_spacing+4) << "STOP");
				break;
			case esvg::render::path_moveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "MOVETO " << it.getPos() );
				break;
			case esvg::render::path_lineTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO " << it.getPos() );
				break;
			case esvg::render::path_lineToH:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO_H " << it.getPos().x());
				break;
			case esvg::render::path_lineToV:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO_V " << it.getPos().y() );
				break;
			case esvg::render::path_curveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "CURVETO " << it.getPos2() << " " << it.getPos1() << " " << it.getPos() );
				break;
			case esvg::render::path_smoothCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "SMOOTH_CURVETO " << it.getPos2() << " " << it.getPos() );
				break;
			case esvg::render::path_bezierCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "BEZIER_CURVETO " << it.getPos1() << " " << it.getPos() );
				break;
			case esvg::render::path_bezierSmoothCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "BEZIER_SMOOTH_CURVETO " << it.getPos() );
				break;
			case esvg::render::path_elliptic:
				SVG_DEBUG(spacingDist(_spacing+4) << "ELLIPTIC ???");
				// show explanation at : http://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
				break;
			default:
				SVG_DEBUG(spacingDist(_spacing+4) << "????" );
				break;
		}
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

void diplayRenderPoints(const std::vector<esvg::render::Point>& listPoints) {
	SVG_VERBOSE(" Display list of points : size=" << listPoints.size());
	for (int32_t iii=0;
	     iii < listPoints.size();
	     ++iii) {
		switch (listPoints[iii].m_type) {
			case esvg::render::Point::type_single:
				SVG_VERBOSE("    [" << iii << "] Find Single " << listPoints[iii].m_pos);
				break;
			case esvg::render::Point::type_start:
				SVG_VERBOSE("    [" << iii << "] Find Start " << listPoints[iii].m_pos);
				break;
			case esvg::render::Point::type_stop:
				SVG_VERBOSE("    [" << iii << "] Find Stop " << listPoints[iii].m_pos);
				break;
			case esvg::render::Point::type_interpolation:
				SVG_VERBOSE("    [" << iii << "] Find interpolation " << listPoints[iii].m_pos);
				break;
			case esvg::render::Point::type_join:
				SVG_VERBOSE("    [" << iii << "] Find Join " << listPoints[iii].m_pos);
				break;
		}
	}
}

std::vector<esvg::render::Point> esvg::render::Path::generateListPoints(int32_t _level, int32_t _recurtionMax, float _threshold) {
	SVG_VERBOSE(spacingDist(_level) << "Generate List Points ... from a path");
	std::vector<esvg::render::Point> out;
	vec2 lastPosition(0.0f, 0.0f);
	int32_t lastPointId = -1;
	bool PathStart = false;
	// Foreach element, we move in the path:
	for(auto &it : m_listElement) {
		switch (it.getType()) {
			case esvg::render::path_stop:
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_stop");
				// TODO : Check if the z value mean that the path will cycle ...
				if (out.size() != 0) {
					if (PathStart == false) {
						SVG_WARNING(spacingDist(_level+1) << " Request path stop of not starting path ...");
					} else {
						out.back().setEndPath();
						PathStart = false;
					}
				}
				// nothing alse to do ...
				break;
			case esvg::render::path_moveTo:
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_moveTo");
				// stop last path
				if (out.size() != 0) {
					if (PathStart == true) {
						out.back().setEndPath();
						PathStart = false;
					}
				}
				PathStart = true;
				// create a new one
				if (it.getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it.getPos();
				out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				break;
			case esvg::render::path_lineTo:
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_lineTo");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
					PathStart = true;
				}
				if (it.getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it.getPos();
				out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				break;
			case esvg::render::path_lineToH:
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_lineToH");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
					PathStart = true;
				}
				if (it.getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it.getPos();
				out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				break;
			case esvg::render::path_lineToV:
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_lineToV");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
					PathStart = true;
				}
				if (it.getRelative() == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += it.getPos();
				out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_start));
				break;
			case esvg::render::path_curveTo:
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_curveTo");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					out.push_back(esvg::render::Point(lastPosition, esvg::render::Point::type_join));
					PathStart = true;
				}
				{
					vec2 lastPosStore(lastPosition);
					if (it.getRelative() == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos1 = lastPosition + it.getPos1();;
					vec2 pos2 = lastPosition + it.getPos2();;
					vec2 pos = lastPosition + it.getPos();;
					interpolateCubicBezier(out,
					                       _recurtionMax,
					                       _threshold,
					                       lastPosStore,
					                       pos1,
					                       pos2,
					                       pos,
					                       0,
					                       esvg::render::Point::type_join);
					lastPosition = pos;
				}
				break;
			case esvg::render::path_smoothCurveTo:
				SVG_TODO(spacingDist(_level+1) << " Draw : esvg::render::path_smoothCurveTo");
				/*
				path.curve4SmoothTo(it.getRelative(),
				                    vec2(it.m_element[0],
				                         it.m_element[1]),
				                    vec2(it.m_element[2],
				                         it.m_element[3]) );
				*/
				break;
			case esvg::render::path_bezierCurveTo:
				SVG_TODO(spacingDist(_level+1) << " Draw : esvg::render::path_bezierCurveTo");
				/*
				path.curve3To(it.getRelative(),
				              vec2(it.m_element[0],
				                   it.m_element[1]),
				              vec2(it.m_element[2],
				                   it.m_element[3]) );
				*/
				break;
			case esvg::render::path_bezierSmoothCurveTo:
				SVG_TODO(spacingDist(_level+1) << " Draw : esvg::render::path_bezierSmoothCurveTo");
				/*
				path.curve3SmoothTo(it.getRelative(),
				                    vec2(it.m_element[0],
				                         it.m_element[1]) );
				*/
				break;
			case esvg::render::path_elliptic:
				/*
				SVG_VERBOSE(spacingDist(_level+1) << " Draw : esvg::render::path_elliptic");
				path.ellipticTo(it.getRelative(),
				                it.m_element[0],
				                it.m_element[1],
				                it.m_element[2],
				                it.m_element[3],
				                it.m_element[4],
				                it.m_element[5],
				                it.m_element[6] );
				*/
				SVG_TODO(spacingDist(_level+1) << " Draw : esvg::render::path_elliptic");
				break;
			default:
				SVG_ERROR(spacingDist(_level+1) << " Unknow PATH commant (internal error)");
				break;
		}
	}
	diplayRenderPoints(out);
	return out;
}
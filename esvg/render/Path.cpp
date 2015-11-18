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


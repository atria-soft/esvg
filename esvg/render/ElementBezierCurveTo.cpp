/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Element.h>
#include <esvg/debug.h>

#undef __class__
#define __class__	"rerder::ElementBezierCurveTo"


esvg::render::ElementBezierCurveTo::ElementBezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos):
  Element(esvg::render::path_bezierCurveTo, _relative) {
	m_pos = _pos;
	m_pos1 = _pos1;
}

std::string esvg::render::ElementBezierCurveTo::display() const {
	return std::string("pos=") + etk::to_string(m_pos) + " pos1=" + etk::to_string(m_pos1);
}
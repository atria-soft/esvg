/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Element.h>
#include <esvg/debug.h>

esvg::render::ElementBezierSmoothCurveTo::ElementBezierSmoothCurveTo(bool _relative, const vec2& _pos):
  Element(esvg::render::path_bezierSmoothCurveTo, _relative) {
	m_pos = _pos;
}


std::string esvg::render::ElementBezierSmoothCurveTo::display() const {
	return std::string("pos=") + etk::to_string(m_pos);
}
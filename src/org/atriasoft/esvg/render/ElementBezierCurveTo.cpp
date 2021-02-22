/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementBezierCurveTo::ElementBezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos):
  Element(esvg::render::path_bezierCurveTo, _relative) {
	m_pos = _pos;
	m_pos1 = _pos1;
}

etk::String esvg::render::ElementBezierCurveTo::display() const {
	return etk::String("pos=") + etk::toString(m_pos) + " pos1=" + etk::toString(m_pos1);
}
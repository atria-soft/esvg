/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementSmoothCurveTo::ElementSmoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos):
  Element(esvg::render::path_smoothCurveTo, _relative) {
	m_pos = _pos;
	m_pos2 = _pos2;
}


etk::String esvg::render::ElementSmoothCurveTo::display() const {
	return etk::String("pos=") + etk::toString(m_pos) + " pos2=" + etk::toString(m_pos2);
}
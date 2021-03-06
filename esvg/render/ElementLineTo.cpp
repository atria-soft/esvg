/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementLineTo::ElementLineTo(bool _relative, const vec2& _pos):
  Element(esvg::render::path_lineTo, _relative) {
	m_pos = _pos;
}


etk::String esvg::render::ElementLineTo::display() const {
	return etk::String("pos=") + etk::toString(m_pos);
}
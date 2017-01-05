/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementMoveTo::ElementMoveTo(bool _relative, const vec2& _pos):
  Element(esvg::render::path_moveTo, _relative) {
	m_pos = _pos;
}


std::string esvg::render::ElementMoveTo::display() const {
	return std::string("pos=") + etk::to_string(m_pos);
}
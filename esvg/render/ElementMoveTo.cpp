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
#define __class__	"rerder::ElementMoveTo"

esvg::render::ElementMoveTo::ElementMoveTo(bool _relative, const vec2& _pos):
  Element(esvg::render::path_moveTo, _relative) {
	m_pos = _pos;
}


std::string esvg::render::ElementMoveTo::display() const {
	return std::string("pos=") + etk::to_string(m_pos);
}
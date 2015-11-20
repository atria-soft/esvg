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
#define __class__	"rerder::ElementSmoothCurveTo"

esvg::render::ElementSmoothCurveTo::ElementSmoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos):
  Element(esvg::render::path_smoothCurveTo, _relative) {
	m_pos = _pos;
	m_pos2 = _pos2;
}


std::string esvg::render::ElementSmoothCurveTo::display() const {
	return std::string("pos=") + etk::to_string(m_pos) + " pos2=" + etk::to_string(m_pos2);
}
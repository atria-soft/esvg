/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Element.h>
#include <esvg/debug.h>

esvg::render::ElementLineToV::ElementLineToV(bool _relative, float _posY):
  Element(esvg::render::path_lineToV, _relative) {
	m_pos = vec2(0.0f, _posY);
}


std::string esvg::render::ElementLineToV::display() const {
	return std::string("posY=") + etk::to_string(m_pos.y());
}
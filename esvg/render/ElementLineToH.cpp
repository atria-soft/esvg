/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Element.h>
#include <esvg/debug.h>

esvg::render::ElementLineToH::ElementLineToH(bool _relative, float _posX):
  Element(esvg::render::path_lineToH, _relative) {
	m_pos = vec2(_posX, 0.0f);
}


std::string esvg::render::ElementLineToH::display() const {
	return std::string("posX=") + etk::to_string(m_pos.x());
}
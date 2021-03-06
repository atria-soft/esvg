/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementLineToV::ElementLineToV(bool _relative, float _posY):
  Element(esvg::render::path_lineToV, _relative) {
	m_pos = vec2(0.0f, _posY);
}


etk::String esvg::render::ElementLineToV::display() const {
	return etk::String("posY=") + etk::toString(m_pos.y());
}
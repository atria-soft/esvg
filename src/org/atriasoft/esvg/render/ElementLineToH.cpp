/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementLineToH::ElementLineToH(bool _relative, float _posX):
  Element(esvg::render::path_lineToH, _relative) {
	m_pos = vec2(_posX, 0.0f);
}


etk::String esvg::render::ElementLineToH::display() const {
	return etk::String("posX=") + etk::toString(m_pos.x());
}
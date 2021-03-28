/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementLineToV::ElementLineToV(boolean _relative, float _posY):
  Element(esvg::render::path_lineToV, _relative) {
	this.pos = Vector2f(0.0f, _posY);
}


etk::String esvg::render::ElementLineToV::display() const {
	return etk::String("posY=") + etk::toString(this.pos.y());
}
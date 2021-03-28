/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementMoveTo::ElementMoveTo(boolean _relative, const Vector2f& _pos):
  Element(esvg::render::path_moveTo, _relative) {
	this.pos = _pos;
}


etk::String esvg::render::ElementMoveTo::display() const {
	return etk::String("pos=") + etk::toString(this.pos);
}
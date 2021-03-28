/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementLineTo::ElementLineTo(boolean _relative, const Vector2f& _pos):
  Element(esvg::render::path_lineTo, _relative) {
	this.pos = _pos;
}


etk::String esvg::render::ElementLineTo::display() const {
	return etk::String("pos=") + etk::toString(this.pos);
}
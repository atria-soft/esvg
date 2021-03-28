/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementCurveTo::ElementCurveTo(boolean _relative, const Vector2f& _pos1, const Vector2f& _pos2, const Vector2f& _pos):
  Element(esvg::render::path_curveTo, _relative) {
	this.pos = _pos;
	this.pos1 = _pos1;
	this.pos2 = _pos2;
}



etk::String esvg::render::ElementCurveTo::display() const {
	return etk::String("pos=") + etk::toString(this.pos) + " pos1=" + etk::toString(this.pos1) + " pos2=" + etk::toString(this.pos2);
}
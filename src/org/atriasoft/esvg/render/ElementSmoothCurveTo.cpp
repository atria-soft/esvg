/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementSmoothCurveTo::ElementSmoothCurveTo(boolean _relative, const Vector2f& _pos2, const Vector2f& _pos):
  Element(esvg::render::path_smoothCurveTo, _relative) {
	this.pos = _pos;
	this.pos2 = _pos2;
}


etk::String esvg::render::ElementSmoothCurveTo::display() const {
	return etk::String("pos=") + etk::toString(this.pos) + " pos2=" + etk::toString(this.pos2);
}
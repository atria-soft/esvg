/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementElliptic::ElementElliptic(boolean _relative,
                                               const Vector2f& _radius, // in this.vec1
                                               float _angle,
                                               boolean _largeArcFlag,
                                               boolean _sweepFlag,
                                               const Vector2f& _pos):
  Element(esvg::render::path_elliptic, _relative) {
	this.pos1 = _radius;
	this.pos = _pos;
	this.angle = _angle;
	this.largeArcFlag = _largeArcFlag;
	this.sweepFlag = _sweepFlag;
}


etk::String esvg::render::ElementElliptic::display() const {
	return etk::String("pos=") + etk::toString(this.pos)
	       + " radius=" + etk::toString(this.pos1)
	       + " angle=" + etk::toString(this.angle)
	       + " largeArcFlag=" + etk::toString(this.largeArcFlag)
	       + " sweepFlag=" + etk::toString(this.sweepFlag);
}
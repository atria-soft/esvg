/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Point.hpp>
#include <esvg/debug.hpp>

void esvg::render::Point::setEndPath() {
	if (this.type == esvg::render::Point::type::interpolation) {
		Log.warning("Request stop path of an interpolate Point");
		this.type = esvg::render::Point::type::stop;
		return;
	}
	if (this.type == esvg::render::Point::type::stop) {
		Log.warning("Request stop path of an STOP Point");
		return;
	}
	if (this.type == esvg::render::Point::type::start) {
		this.type = esvg::render::Point::type::single;
		return;
	}
	this.type = esvg::render::Point::type::stop;
}

void esvg::render::Point::normalize(const Vector2f& _nextPoint) {
	this.delta = _nextPoint - this.pos;
	this.len = this.delta.length();
}


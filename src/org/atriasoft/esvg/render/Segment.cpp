/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Segment.hpp>
#include <esvg/debug.hpp>

esvg::render::Segment::Segment() {
	p0 = vec2(0,0);
	p1 = vec2(0,0);
	direction = 0;
}

esvg::render::Segment::Segment(const vec2& _p0, const vec2& _p1) {
	// segment register all time the lower at P0n then we need to register the sens of the path
	p0 = _p0;
	p1 = _p1;
	direction = 0;
}

void esvg::render::Segment::applyMatrix(const mat2x3& _transformationMatrix) {
	p0 = _transformationMatrix * p0;
	p1 = _transformationMatrix * p1;
	createDirection();
}

void esvg::render::Segment::createDirection() {
	if (p0.y() < p1.y()) {
		direction = 1; // direction like clock
	} else {
		vec2 tmp(p0);
		p0 = p1;
		p1 = tmp;
		direction = -1; // direction like anti-clock
	}
}


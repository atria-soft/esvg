/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Segment.h>
#include <esvg/debug.h>

#undef __class__
#define __class__	"rerder::Segment"

esvg::render::Segment::Segment(const vec2& _p0, const vec2& _p1) {
	// segment register all time the lower at P0n then we need to register the sens of the path
	if (_p0.y() < _p1.y()) {
		p0 = _p0;
		p1 = _p1;
		direction = 1; // direction like clock
	} else {
		p0 = _p1;
		p1 = _p0;
		direction = -1; // direction like anti-clock
	}
}



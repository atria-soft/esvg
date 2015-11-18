/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_SEGMENT_H__
#define __ESVG_RENDER_SEGMENT_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>

namespace esvg {
	namespace render {
		class Segment {
			public:
				Segment(const vec2& _p0, const vec2& _p1);
				vec2 p0;
				vec2 p1;
				float direction;
		};
	}
}

#endif

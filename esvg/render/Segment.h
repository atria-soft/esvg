/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <etk/math/Matrix2.h>

namespace esvg {
	namespace render {
		class Segment {
			public:
				Segment(const vec2& _p0, const vec2& _p1);
				vec2 p0;
				vec2 p1;
				int32_t direction;
				void applyMatrix(const mat2& _transformationMatrix);
				void createDirection();
		};
	}
}


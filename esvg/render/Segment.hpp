/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/math/Matrix2x3.hpp>

namespace esvg {
	namespace render {
		class Segment {
			public:
				Segment(const vec2& _p0, const vec2& _p1);
				vec2 p0;
				vec2 p1;
				int32_t direction;
				void applyMatrix(const mat2x3& _transformationMatrix);
				void createDirection();
		};
	}
}


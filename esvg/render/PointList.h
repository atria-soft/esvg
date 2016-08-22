/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <etk/math/Matrix2.h>
#include <esvg/render/Element.h>
#include <esvg/render/Point.h>

namespace esvg {
	namespace render {
		class PointList {
			public:
				std::vector<std::vector<esvg::render::Point>> m_data;
			public:
				PointList();
				void addList(std::vector<esvg::render::Point>& _list);
				void display();
				void applyMatrix(const mat2& _transformationMatrix);
				std::pair<vec2, vec2> getViewPort();
		};
	}
}

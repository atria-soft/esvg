/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/math/Matrix2.hpp>
#include <esvg/render/Element.hpp>
#include <esvg/render/Point.hpp>

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
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/math/Matrix2x3.hpp>
#include <etk/Pair.hpp>
#include <esvg/render/Element.hpp>
#include <esvg/render/Point.hpp>

namespace esvg {
	namespace render {
		class PointList {
			public:
				List<List<esvg::render::Point>> m_data;
			public:
				PointList();
				void addList(List<esvg::render::Point>& _list);
				void display();
				void applyMatrix(const mat2x3& _transformationMatrix);
				etk::Pair<Vector2f, Vector2f> getViewPort();
		};
	}
}

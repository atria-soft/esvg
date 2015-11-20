/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_POINT_LIST_H__
#define __ESVG_RENDER_POINT_LIST_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
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
		};
	}
}

#endif


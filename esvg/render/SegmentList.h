/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_SEGMENT_LIST_H__
#define __ESVG_RENDER_SEGMENT_LIST_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Segment.h>
#include <esvg/render/PointList.h>

namespace esvg {
	namespace render {
		class SegmentList {
			public:
				std::vector<esvg::render::Segment> m_data;
			public:
				SegmentList();
				void addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1);
				void createSegmentList(const esvg::render::PointList& _listPoint);
				void createSegmentListStroke(esvg::render::PointList& _listPoint, float _width);
		};
	}
}

#endif

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
#include <esvg/cap.h>
#include <esvg/join.h>
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
				void createSegmentListStroke(esvg::render::PointList& _listPoint,
				                             float _width,
				                             enum esvg::cap _cap,
				                             enum esvg::join _join,
				                             float _miterLimit);
			private:
				void startStopPoint(vec2& _leftPoint,
				                    vec2& _rightPoint,
				                    const esvg::render::Point& _point,
				                    enum esvg::cap _cap,
				                    float _width,
				                    bool _isStart);
				void createSegmentListStroke(const vec2& _point1,
				                             const vec2& _point2,
				                             const vec2& _center,
				                             float _width,
				                             bool _isStart);
			public:
				std::pair<vec2, vec2> getViewPort();
				void applyMatrix(const mat2& _transformationMatrix);
		};
	}
}

#endif

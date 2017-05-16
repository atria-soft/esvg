/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <esvg/cap.hpp>
#include <esvg/join.hpp>
#include <esvg/render/Segment.hpp>
#include <esvg/render/PointList.hpp>

namespace esvg {
	namespace render {
		class SegmentList {
			public:
				std::vector<esvg::render::Segment> m_data;
			public:
				SegmentList();
				#ifdef DEBUG
					void addSegment(const vec2& _pos0, const vec2& _pos1);
				#endif
				void addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1);
				void addSegment(const esvg::render::Point& _pos0, const esvg::render::Point& _pos1, bool _disableHorizontal);
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
				void applyMatrix(const mat2x3& _transformationMatrix);
		};
	}
}

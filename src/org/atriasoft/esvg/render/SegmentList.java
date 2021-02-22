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
				List<esvg::render::Segment> m_data;
			public:
				SegmentList();
				#ifdef DEBUG
					void addSegment(const Vector2f& _pos0, const Vector2f& _pos1);
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
				void startStopPoint(Vector2f& _leftPoint,
				                    Vector2f& _rightPoint,
				                    const esvg::render::Point& _point,
				                    enum esvg::cap _cap,
				                    float _width,
				                    bool _isStart);
				void createSegmentListStroke(const Vector2f& _point1,
				                             const Vector2f& _point2,
				                             const Vector2f& _center,
				                             float _width,
				                             bool _isStart);
			public:
				etk::Pair<Vector2f, Vector2f> getViewPort();
				void applyMatrix(const mat2x3& _transformationMatrix);
		};
	}
}

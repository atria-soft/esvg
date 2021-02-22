/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>

namespace esvg {
	class Line : public esvg::Base {
		private:
			Vector2f m_startPos; //!< Start line position
			Vector2f m_stopPos; //!< Stop line position
		public:
			Line(PaintState _parentPaintState);
			~Line();
			bool parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) override;
			void display(int32_t _spacing) override;
			void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) override;
			void drawShapePoints(List<List<Vector2f>>& _out,
			                     int32_t _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int32_t _level=1) override;
		private:
			esvg::render::Path createPath();
	};
}


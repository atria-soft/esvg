/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>

namespace esvg {
	class Rectangle : public esvg::Base {
		private:
			vec2 m_position; //!< position of the rectangle
			vec2 m_size; //!< size of the rectangle
			vec2 m_roundedCorner; //!< property of the rounded corner
		public:
			Rectangle(PaintState _parentPaintState);
			~Rectangle();
			bool parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) override;
			void display(int32_t _spacing) override;
			void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) override;
			void drawShapePoints(std::vector<std::vector<vec2>>& _out,
			                     int32_t _recurtionMax,
			                     float _threshold,
			                     mat2& _basicTrans,
			                     int32_t _level=1) override;
		private:
			esvg::render::Path createPath();
	};
}


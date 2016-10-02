/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>

namespace esvg {
	class Ellipse : public esvg::Base {
		private:
			vec2 m_c; //!< Center property of the ellipse
			vec2 m_r; //!< Radius property of the ellipse
		public:
			Ellipse(PaintState _parentPaintState);
			~Ellipse();
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

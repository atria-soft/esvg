/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>
#include <esvg/render/Path.hpp>

namespace esvg {
	class Path : public esvg::Base {
		public:
			esvg::render::Path m_listElement;
		public:
			Path(PaintState _parentPaintState);
			~Path();
			bool parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax) override;
			void display(int32_t _spacing) override;
			void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) override;
			void drawShapePoints(std::vector<std::vector<vec2>>& _out,
			                     int32_t _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int32_t _level=1) override;
	};
}


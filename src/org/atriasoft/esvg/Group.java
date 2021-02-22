/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>
#include <etk/Vector.hpp>

namespace esvg {
	class Group : public esvg::Base {
		private:
			etk::Vector<ememory::SharedPtr<esvg::Base>> m_subElementList;  //!< sub elements ...
		public:
			Group(PaintState _parentPaintState);
			~Group();
			bool parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax) override;
			void display(int32_t spacing) override;
			void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) override;
			void drawShapePoints(etk::Vector<etk::Vector<vec2>>& _out,
			                     int32_t _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int32_t _level=1) override;
	};
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>

namespace esvg {
	class Text : public esvg::Base {
		public:
			Text(PaintState _parentPaintState);
			~Text();
			bool parse(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax);
			void display(int32_t _spacing) override;
	};
}


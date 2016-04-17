/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>

namespace esvg {
	namespace render {
		class ElementLineToH : public esvg::render::Element {
			public:
				ElementLineToH(bool _relative, float _posX);
			public:
				virtual std::string display() const;
		};
	}
}


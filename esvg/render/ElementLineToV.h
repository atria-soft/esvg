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
		class ElementLineToV : public esvg::render::Element {
			public:
				ElementLineToV(bool _relative, float _posY);
			public:
				virtual std::string display() const;
		};
	}
}



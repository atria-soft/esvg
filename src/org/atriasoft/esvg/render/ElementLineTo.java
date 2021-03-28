package org.atriasoft.esvg.render;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <esvg/render/Element.hpp>

namespace esvg {
	namespace render {
		class ElementLineTo  extends  esvg::render::Element {
			public:
				ElementLineTo(boolean _relative, const Vector2f& _pos);
			public:
				virtual etk::String display() const;
		};
	}
}


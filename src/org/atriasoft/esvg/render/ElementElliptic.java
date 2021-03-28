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
		class ElementElliptic  extends  esvg::render::Element {
			public:
				float this.angle;
				boolean this.largeArcFlag;
				boolean this.sweepFlag;
			public:
				ElementElliptic(boolean _relative,
				                const Vector2f& _radius, // in this.pos1
				                float _angle,
				                boolean _largeArcFlag,
				                boolean _sweepFlag,
				                const Vector2f& _pos);
			public:
				virtual etk::String display() const;
		};
	}
}


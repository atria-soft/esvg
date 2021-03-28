package org.atriasoft.esvg.render;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/math/Vector2D.hpp>#include<esvg/render/Element.hpp>

namespace esvg{namespace render{
class ElementLineToV extends esvg::render::Element
{
			public:
	
	ElementLineToV(boolean _relative, float _posY);public:
	
	virtual etk::String display() const;
		};
}}

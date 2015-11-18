/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_ELEMENT_LINE_TO_V_H__
#define __ESVG_RENDER_ELEMENT_LINE_TO_V_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>

namespace esvg {
	namespace render {
		class ElementLineToV : public Element {
			public:
				ElementLineToV(bool _relative, float _posY):
				  Element(esvg::render::path_lineToV, _relative) {
					m_pos = vec2(0.0f, _posY);
				}
		};
	}
}

#endif


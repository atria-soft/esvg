/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_ELEMENT_SMOOTH_CURVE_TO_H__
#define __ESVG_RENDER_ELEMENT_SMOOTH_CURVE_TO_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>

namespace esvg {
	namespace render {
		class ElementSmoothCurveTo : public Element {
			public:
				ElementSmoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos):
				  Element(esvg::render::path_smoothCurveTo, _relative) {
					m_pos = _pos;
					m_pos2 = _pos2;
				}
		};
	}
}

#endif


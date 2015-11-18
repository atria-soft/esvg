/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_ELEMENT_BEZIER_CURVE_TO_H__
#define __ESVG_RENDER_ELEMENT_BEZIER_CURVE_TO_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>

namespace esvg {
	namespace render {
		class ElementBezierCurveTo : public Element {
			public:
				ElementBezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos):
				  Element(esvg::render::path_bezierCurveTo, _relative) {
					m_pos = _pos;
					m_pos1 = _pos1;
				}
		};
	}
}

#endif


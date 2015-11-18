/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_ELEMENT_ELLIPTIC_H__
#define __ESVG_RENDER_ELEMENT_ELLIPTIC_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>

namespace esvg {
	namespace render {
		class ElementElliptic : public Element {
			public:
				ElementElliptic(bool _relative, float _val0, float _val1, float _val2, float _val3, float _val4, float _val5, float _val6):
				  Element(esvg::render::path_elliptic, _relative) {
					// TODO ... later ...
				}
		};
	}
}

#endif


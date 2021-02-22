/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <esvg/render/Element.hpp>

namespace esvg {
	namespace render {
		class ElementCurveTo : public esvg::render::Element {
			public:
				ElementCurveTo(bool _relative, const Vector2f& _pos1, const Vector2f& _pos2, const Vector2f& _pos);
			public:
				virtual etk::String display() const;
		};
	}
}


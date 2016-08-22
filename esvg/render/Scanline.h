/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/math/Vector2D.h>

namespace esvg {
	namespace render {
		class Scanline {
			private:
				std::vector<float> m_data;
			public:
				// constructor :
				Scanline(size_t _size=32);
				// destructor
				~Scanline() { };
			public:
				size_t size() const;
				void clear(float _fill);
				float get(int32_t _pos) const;
				void set(int32_t _pos, float _newColor);
		};
	}
}


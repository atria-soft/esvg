/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDERER_H__
#define __ESVG_RENDERER_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>

namespace esvg {
	
	class Renderer {
		public:
			std::vector<uint8_t> m_scanline;
			std::vector<uint8_t> m_buffer;
			ivec2 m_size;
			int32_t m_stride;
		public:
			Renderer(const ivec2& _size);
			~Renderer();
			void writePpm(std::string fileName);
			uint8_t* getDataPointer() {
				return &m_buffer[0];
			};
			uint32_t getDataSize() {
				return m_buffer.size();
			};
	};
};

#endif

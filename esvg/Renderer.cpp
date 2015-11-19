/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Renderer.h>

// 4 is for the RGBA ...
#define DATA_ALLOCATION_ELEMENT (4)

#undef __class__
#define __class__ "Renderer"

esvg::Renderer::Renderer(const ivec2& _size) {
	m_size = _size;
	m_buffer.resize(m_size.x() * m_size.y() * DATA_ALLOCATION_ELEMENT, 0);
}

esvg::Renderer::~Renderer() {
	m_buffer.clear();
	m_stride = 0;
	m_size = ivec2(0,0);
}

void esvg::Renderer::print(const esvg::render::Weight& _weightFill,
                           const etk::Color<uint8_t,4>& _colorFill,
                           const esvg::render::Weight& _weightStroke,
                           const etk::Color<uint8_t,4>& _colorStroke) {
	if (_colorFill.a() == 0x00) {
		if (_colorStroke.a() != 0x00) {
			// only stroke
			for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
				for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
					ivec2 pos(xxx, yyy);
					float valueStroke = _weightStroke.get(pos);
					if (valueStroke != 0.0f) {
						m_buffer[(m_size.x()*yyy + xxx)*4    ] = uint8_t(valueStroke*_colorStroke.r());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 1] = uint8_t(valueStroke*_colorStroke.g());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 2] = uint8_t(valueStroke*_colorStroke.b());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 3] = uint8_t(valueStroke*_colorStroke.a());
					}
				}
			}
		}
	} else {
		if (_colorStroke.a() == 0x00) {
			// only Fill
			for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
				for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
					ivec2 pos(xxx, yyy);
					float valueFill = _weightFill.get(pos);
					if (valueFill != 0.0f) {
						m_buffer[(m_size.x()*yyy + xxx)*4    ] = uint8_t(valueFill*_colorFill.r());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 1] = uint8_t(valueFill*_colorFill.g());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 2] = uint8_t(valueFill*_colorFill.b());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 3] = uint8_t(valueFill*_colorFill.a());
					}
				}
			}
		} else {
			// all together 
			for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
				for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
					ivec2 pos(xxx, yyy);
					float valueFill = _weightFill.get(pos);
					float valueStroke = _weightStroke.get(pos);
					if (valueStroke != 0.0f) {
						m_buffer[(m_size.x()*yyy + xxx)*4    ] = uint8_t(valueStroke*_colorStroke.r());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 1] = uint8_t(valueStroke*_colorStroke.g());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 2] = uint8_t(valueStroke*_colorStroke.b());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 3] = uint8_t(valueStroke*_colorStroke.a());
					} else {
						m_buffer[(m_size.x()*yyy + xxx)*4    ] = uint8_t(valueFill*_colorFill.r());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 1] = uint8_t(valueFill*_colorFill.g());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 2] = uint8_t(valueFill*_colorFill.b());
						m_buffer[(m_size.x()*yyy + xxx)*4 + 3] = uint8_t(valueFill*_colorFill.a());
					}
				}
			}
		}
	}
}

// Writing the buffer to a .PPM file, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
void esvg::Renderer::writePpm(std::string fileName) {
	if (m_buffer.size() == 0) {
		return;
	}
	FILE* fd = fopen(fileName.c_str(), "wb");
	if(fd != nullptr) {
		int32_t sizeX = m_size.x();
		int32_t sizeY = m_size.y();
		SVG_DEBUG("Generate ppm : " << m_size);
		fprintf(fd, "P6 %d %d 255 ", sizeX, sizeY);
		for (int32_t iii=0 ; iii<sizeX*sizeY; iii++) {
			fwrite(&m_buffer[iii*DATA_ALLOCATION_ELEMENT], 1, 3, fd);
		}
		fclose(fd);
	}
}





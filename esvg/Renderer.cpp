/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Renderer.h>
#include <etk/os/FSNode.h>

// 4 is for the RGBA ...
#define DATA_ALLOCATION_ELEMENT (4)

#undef __class__
#define __class__ "Renderer"

esvg::Renderer::Renderer(const ivec2& _size, bool _visualDebug) :
#ifdef DEBUG
  m_visualDebug(_visualDebug),
  m_factor(1),
#endif
  m_interpolationRecurtionMax(10),
  m_interpolationThreshold(0.25f),
  m_nbSubScanLine(8) {
	#ifdef DEBUG
		if (m_visualDebug == true) {
			m_factor = 10;
		}
	#endif
	setSize(_size);
}

esvg::Renderer::~Renderer() {
	m_buffer.clear();
	m_size = ivec2(0,0);
}

etk::Color<float,4> esvg::Renderer::mergeColor(etk::Color<float,4> _base, etk::Color<float,4> _integration) {
	etk::Color<float,4> result;
	/*
	if (_integration.a() < _base.a()) {
		result = _integration;
		_integration = _base;
		_base = result;
	}
	*/
	result.setR(_integration.a() * _integration.r() + _base.a() * (1.0f - _integration.a()) * _base.r());
	result.setG(_integration.a() * _integration.g() + _base.a() * (1.0f - _integration.a()) * _base.g());
	result.setB(_integration.a() * _integration.b() + _base.a() * (1.0f - _integration.a()) * _base.b());
	result.setA(_integration.a() + _base.a() * (1.0f - _integration.a()));
	if (result.a() != 0.0f) {
		float reverse = 1.0f/result.a();
		result.setR(result.r()*reverse);
		result.setG(result.g()*reverse);
		result.setB(result.b()*reverse);
	}
	return result;
}

void esvg::Renderer::print(const esvg::render::Weight& _weightFill,
                           const etk::Color<float,4>& _colorFill,
                           const esvg::render::Weight& _weightStroke,
                           const etk::Color<float,4>& _colorStroke,
                           float _opacity) {
	int32_t sizeX = m_size.x();
	int32_t sizeY = m_size.y();
	#if DEBUG
		sizeX *= m_factor;
		sizeY *= m_factor;
	#endif
	if (_colorFill.a() == 0x00) {
		if (_colorStroke.a() != 0x00) {
			// only stroke
			for (int32_t yyy=0; yyy<sizeY; ++yyy) {
				for (int32_t xxx=0; xxx<sizeX; ++xxx) {
					#if DEBUG
						ivec2 pos(xxx/m_factor, yyy/m_factor);
					#else
						ivec2 pos(xxx, yyy);
					#endif
					float valueStroke = _weightStroke.get(pos);
					if (valueStroke != 0.0f) {
						// set a ratio of the merging value
						etk::Color<float,4> tmpColor = _colorStroke * valueStroke;
						tmpColor.setA(tmpColor.a() * _opacity);
						// integrate the value at the previous color
						m_buffer[sizeX*yyy + xxx] = mergeColor(m_buffer[sizeX*yyy + xxx], tmpColor);
					}
				}
			}
		}
	} else {
		if (_colorStroke.a() == 0x00) {
			// only Fill
			for (int32_t yyy=0; yyy<sizeY; ++yyy) {
				for (int32_t xxx=0; xxx<sizeX; ++xxx) {
					#if DEBUG
						ivec2 pos(xxx/m_factor, yyy/m_factor);
					#else
						ivec2 pos(xxx, yyy);
					#endif
					float valueFill = _weightFill.get(pos);
					if (valueFill != 0.0f) {
						// set a ratio of the merging value
						etk::Color<float,4> tmpColor = _colorFill * valueFill;
						tmpColor.setA(tmpColor.a() * _opacity);
						// integrate the value at the previous color
						m_buffer[sizeX*yyy + xxx] = mergeColor(m_buffer[sizeX*yyy + xxx], tmpColor);
					}
				}
			}
		} else {
			// all together 
			for (int32_t yyy=0; yyy<sizeY; ++yyy) {
				for (int32_t xxx=0; xxx<sizeX; ++xxx) {
					#if DEBUG
						ivec2 pos(xxx/m_factor, yyy/m_factor);
					#else
						ivec2 pos(xxx, yyy);
					#endif
					float valueFill = _weightFill.get(pos);
					float valueStroke = _weightStroke.get(pos);
					// calculate merge of stroke and fill value:
					etk::Color<float,4> intermediateColorFill = _colorFill;
					intermediateColorFill.setA(intermediateColorFill.a()*valueFill);
					etk::Color<float,4> intermediateColorStroke = _colorStroke;
					intermediateColorStroke.setA(intermediateColorStroke.a()*valueStroke);
					etk::Color<float,4> intermediateColor = mergeColor(intermediateColorFill, intermediateColorStroke);
					intermediateColor.setA(intermediateColor.a() * _opacity);
					m_buffer[sizeX*yyy + xxx] = mergeColor(m_buffer[sizeX*yyy + xxx], intermediateColor);
				}
			}
		}
	}
}

#ifdef DEBUG
	void esvg::Renderer::addDebugSegment(const esvg::render::SegmentList& _listSegment) {
		if (m_visualDebug == false) {
			return;
		}
		ivec2 dynamicSize = m_size * m_factor;
		// for each lines:
		for (int32_t yyy=0; yyy<dynamicSize.y(); ++yyy) {
			// Reduce the number of lines in the subsampling parsing:
			std::vector<esvg::render::Segment> availlableSegmentPixel;
			for (auto &it : _listSegment.m_data) {
				if (    it.p0.y() * m_factor <= float(yyy+1)
				     && it.p1.y() * m_factor >= float(yyy)) {
					availlableSegmentPixel.push_back(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + 0.5f;
			std::vector<esvg::render::Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    it.p0.y() * m_factor <= subSamplingCenterPos
				     && it.p1.y() * m_factor >= subSamplingCenterPos ) {
					availlableSegment.push_back(it);
				}
			}
			// x position, angle
			std::vector<std::pair<float, float>> listPosition;
			for (auto &it : availlableSegment) {
				vec2 delta = it.p0 * m_factor - it.p1 * m_factor;
				// x = coefficent*y+bbb;
				float coefficient = delta.x()/delta.y();
				float bbb = it.p0.x() * m_factor - coefficient*it.p0.y() * m_factor;
				float xpos = coefficient * subSamplingCenterPos + bbb;
				if (    xpos >= 0
				     && xpos < dynamicSize.x()
				     && yyy >= 0
				     && yyy < dynamicSize.y() ) {
					if (it.direction == 1.0f) {
						m_buffer[(dynamicSize.x()*yyy + int32_t(xpos))] = etk::color::blue;
					} else {
						m_buffer[(dynamicSize.x()*yyy + int32_t(xpos))] = etk::color::darkRed;
					}
				}
			}
		}
		// for each colomn:
		for (int32_t xxx=0; xxx<dynamicSize.x(); ++xxx) {
			// Reduce the number of lines in the subsampling parsing:
			std::vector<esvg::render::Segment> availlableSegmentPixel;
			for (auto &it : _listSegment.m_data) {
				if (    (    it.p0.x() * m_factor <= float(xxx+1)
				          && it.p1.x() * m_factor >= float(xxx) )
				     || (    it.p0.x() * m_factor >= float(xxx+1)
				          && it.p1.x() * m_factor <= float(xxx) ) ) {
					availlableSegmentPixel.push_back(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = xxx + 0.5f;
			std::vector<esvg::render::Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    (    it.p0.x() * m_factor <= subSamplingCenterPos
				          && it.p1.x() * m_factor >= subSamplingCenterPos)
				     || (    it.p0.x() * m_factor >= subSamplingCenterPos
				          && it.p1.x() * m_factor <= subSamplingCenterPos) ) {
					availlableSegment.push_back(it);
				}
			}
			// x position, angle
			std::vector<std::pair<float, float>> listPosition;
			for (auto &it : availlableSegment) {
				vec2 delta = it.p0 * m_factor - it.p1 * m_factor;
				// x = coefficent*y+bbb;
				if (delta.x() == 0) {
					continue;
				}
				float coefficient = delta.y()/delta.x();
				float bbb = it.p0.y() * m_factor - coefficient*it.p0.x() * m_factor;
				float ypos = coefficient * subSamplingCenterPos + bbb;
				if (    ypos >= 0
				     && ypos < dynamicSize.y()
				     && xxx >= 0
				     && xxx < dynamicSize.y() ) {
					if (it.direction == 1.0f) {
						m_buffer[(dynamicSize.x()*int32_t(ypos) + xxx)] = etk::color::blue;
					} else {
						m_buffer[(dynamicSize.x()*int32_t(ypos) + xxx)] = etk::color::darkRed;
					}
				}
			}
		}
	}
#endif


void esvg::Renderer::writePPM(const std::string& _fileName) {
	if (m_buffer.size() == 0) {
		return;
	}
	etk::FSNode tmpFile(_fileName);
	if(tmpFile.fileOpenWrite() == false) {
		SVG_ERROR("Can not find the file name=\"" << tmpFile << "\"");
		return;
	}
	int32_t sizeX = m_size.x();
	int32_t sizeY = m_size.y();
	#if DEBUG
		sizeX *= m_factor;
		sizeY *= m_factor;
	#endif
	SVG_DEBUG("Generate ppm : " << m_size << " debug size=" << ivec2(sizeX,sizeY));
	char tmpValue[1024];
	sprintf(tmpValue, "P6 %d %d 255 ", sizeX, sizeY);
	tmpFile.fileWrite(tmpValue,1,sizeof(tmpValue));
	for (int32_t iii=0 ; iii<sizeX*sizeY; iii++) {
		etk::Color<uint8_t,3> tmp = m_buffer[iii];
		tmpFile.fileWrite(&tmp, 1, 3);
	}
	tmpFile.fileClose();
}
#define PLOPPP
extern "C" {
	#pragma pack(push,1)
	struct bitmapFileHeader {
		int16_t bfType;
		int32_t bfSize;
		int32_t bfReserved;
		int32_t bfOffBits;
	};
	struct bitmapInfoHeader {
		int32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		int16_t biPlanes;
		int16_t biBitCount;
		int32_t biCompression;
		int32_t biSizeImage;
		int32_t biXPelsPerMeter;
		int32_t biYPelsPerMeter;
		#ifndef PLOPPP
		int32_t biClrUsed;
		int32_t biClrImportant;
		#else
		// https://en.wikipedia.org/wiki/BMP_file_format / example 2
		int32_t biPaletteNumber;
		int32_t biImportantColor;
		int32_t biBitMaskRed;
		int32_t biBitMaskGreen;
		int32_t biBitMaskBlue;
		int32_t biBitMaskAlpha;
		int32_t biLCSColorSpace;
		int32_t biUnused[16];
		#endif
	};
	#pragma pack(pop)
}
void esvg::Renderer::writeBMP(const std::string& _fileName) {
	if (m_buffer.size() == 0) {
		return;
	}
	etk::FSNode tmpFile(_fileName);
	
	if(tmpFile.fileOpenWrite() == false) {
		SVG_ERROR("Can not find the file name=\"" << tmpFile << "\"");
		return;
	}
	struct bitmapFileHeader fileHeader;
	struct bitmapInfoHeader infoHeader;
	
	int32_t sizeX = m_size.x();
	int32_t sizeY = m_size.y();
	#if DEBUG
		sizeX *= m_factor;
		sizeY *= m_factor;
	#endif
	
	fileHeader.bfType = 0x4D42;
	fileHeader.bfSize = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader) + sizeX*sizeY*4;
	fileHeader.bfReserved = 0;
	fileHeader.bfOffBits = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader);
	
	
	infoHeader.biSize = sizeof(struct bitmapInfoHeader);
	infoHeader.biWidth = sizeX;
	infoHeader.biHeight = sizeY;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 32;
	#ifndef PLOPPP
	infoHeader.biCompression = 0;
	#else
	infoHeader.biCompression = 3;
	#endif
	infoHeader.biSizeImage = sizeX*sizeY*4;
	infoHeader.biXPelsPerMeter = 75;
	infoHeader.biYPelsPerMeter = 75;
	#ifndef PLOPPP
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	#else
	infoHeader.biPaletteNumber = 0;
	infoHeader.biImportantColor = 0;
	infoHeader.biBitMaskRed = 0xFF000000;
	infoHeader.biBitMaskGreen = 0x00FF0000;
	infoHeader.biBitMaskBlue =0x0000FF00;
	infoHeader.biBitMaskAlpha = 0x000000FF;
	infoHeader.biLCSColorSpace = 0x73524742; // "???"
	for (int32_t jjj=0; jjj<16; ++jjj) {
		infoHeader.biUnused[jjj] = 0;
	}
	infoHeader.biUnused[12] = 0x00000002;
	#endif
	// get the data : 
	tmpFile.fileWrite(&fileHeader, sizeof(struct bitmapFileHeader), 1);
	tmpFile.fileWrite(&infoHeader, sizeof(struct bitmapInfoHeader), 1);
	
	uint8_t data[16];
	for(int32_t yyy=sizeY-1; yyy>=0; --yyy) {
		for(int32_t xxx=0; xxx<sizeX; ++xxx) {
			const etk::Color<uint8_t,4>& tmpColor = m_buffer[sizeX*yyy + xxx];
			uint8_t* pointer = data;
			#ifndef PLOPPP
			*pointer++ = tmpColor.a();
			*pointer++ = tmpColor.r();
			*pointer++ = tmpColor.g();
			*pointer++ = tmpColor.b();
			#else
			*pointer++ = tmpColor.a();
			*pointer++ = tmpColor.b();
			*pointer++ = tmpColor.g();
			*pointer++ = tmpColor.r();
			#endif
			tmpFile.fileWrite(data,1,4);
		}
	}
	tmpFile.fileClose();
}


void esvg::Renderer::setSize(const ivec2& _size) {
	m_size = _size;
	m_buffer.resize(m_size.x() * m_size.y()
	#if DEBUG
	  * m_factor * m_factor
	#endif
	  , etk::color::none);
}

const ivec2& esvg::Renderer::getSize() const {
	return m_size;
}

std::vector<etk::Color<float,4>> esvg::Renderer::getData() {
	return m_buffer;
}




void esvg::Renderer::setInterpolationRecurtionMax(int32_t _value) {
	m_interpolationRecurtionMax = std::avg(1, _value, 200);
}

int32_t esvg::Renderer::getInterpolationRecurtionMax() const {
	return m_interpolationRecurtionMax;
}

void esvg::Renderer::setInterpolationThreshold(float _value) {
	m_interpolationThreshold = std::avg(0.0f, _value, 20000.0f);
}

float esvg::Renderer::getInterpolationThreshold() const {
	return m_interpolationThreshold;
}

void esvg::Renderer::setNumberSubScanLine(int32_t _value) {
	m_nbSubScanLine = std::avg(1, _value, 200);
}

int32_t esvg::Renderer::getNumberSubScanLine() const {
	return m_nbSubScanLine;
}



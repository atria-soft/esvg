/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Renderer.hpp>
#include <etk/os/FSNode.hpp>

esvg::Renderer::Renderer(const ivec2& _size, esvg::Document* _document, bool _visualDebug) :
#ifdef DEBUG
  m_visualDebug(_visualDebug),
  m_factor(1),
#endif
  m_interpolationRecurtionMax(10),
  m_interpolationThreshold(0.25f),
  m_nbSubScanLine(8),
  m_document(_document) {
	#ifdef DEBUG
		if (m_visualDebug == true) {
			m_factor = 20;
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
                           ememory::SharedPtr<esvg::render::DynamicColor>& _colorFill,
                           const esvg::render::Weight& _weightStroke,
                           ememory::SharedPtr<esvg::render::DynamicColor>& _colorStroke,
                           float _opacity) {
	if (_colorFill != nullptr) {
		//_colorFill->setViewPort(etk::Pair<vec2, vec2>(vec2(0,0), vec2(sizeX, sizeY)));
		_colorFill->generate(m_document);
	}
	if (_colorStroke != nullptr) {
		//_colorStroke->setViewPort(etk::Pair<vec2, vec2>(vec2(0,0), vec2(sizeX, sizeY)));
		_colorStroke->generate(m_document);
	}
	// all together
	for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
		for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
			ivec2 pos(xxx, yyy);
			float valueFill = _weightFill.get(pos);
			float valueStroke = _weightStroke.get(pos);
			// calculate merge of stroke and fill value:
			etk::Color<float,4> intermediateColorFill(etk::color::none);
			etk::Color<float,4> intermediateColorStroke(etk::color::none);
			if (    _colorFill != nullptr
			     && valueFill != 0.0f) {
				intermediateColorFill = _colorFill->getColor(pos);
				intermediateColorFill.setA(intermediateColorFill.a()*valueFill);
			}
			if (    _colorStroke != nullptr
			     && valueStroke != 0.0f) {
				intermediateColorStroke = _colorStroke->getColor(pos);
				intermediateColorStroke.setA(intermediateColorStroke.a()*valueStroke);
			}
			etk::Color<float,4> intermediateColor = mergeColor(intermediateColorFill, intermediateColorStroke);
			intermediateColor.setA(intermediateColor.a() * _opacity);
			#if DEBUG
				for (int32_t deltaY=0; deltaY<m_factor; ++deltaY) {
					for (int32_t deltaX=0; deltaX<m_factor; ++deltaX) {
						int32_t id = m_size.x()*m_factor*(yyy*m_factor+deltaY) + (xxx*m_factor+deltaX);
						m_buffer[id] = mergeColor(m_buffer[id], intermediateColor);
					}
				}
			#else
				m_buffer[m_size.x()*yyy + xxx] = mergeColor(m_buffer[m_size.x()*yyy + xxx], intermediateColor);
			#endif
		}
	}
	#ifdef DEBUG
		// display the gradient position:
		ememory::SharedPtr<esvg::render::DynamicColorSpecial> tmpColor = ememory::dynamicPointerCast<esvg::render::DynamicColorSpecial>(_colorFill);
		if (tmpColor != nullptr) {
			esvg::render::SegmentList listSegment;
			// Display bounding box
			listSegment.addSegment(esvg::render::Point(tmpColor->m_viewPort.first),
			                       esvg::render::Point(vec2(tmpColor->m_viewPort.first.x(), tmpColor->m_viewPort.second.y()) ),
			                       false);
			listSegment.addSegment(esvg::render::Point(vec2(tmpColor->m_viewPort.first.x(), tmpColor->m_viewPort.second.y()) ),
			                       esvg::render::Point(tmpColor->m_viewPort.second),
			                       false);
			listSegment.addSegment(esvg::render::Point(tmpColor->m_viewPort.second),
			                       esvg::render::Point(vec2(tmpColor->m_viewPort.second.x(), tmpColor->m_viewPort.first.y()) ),
			                       false);
			listSegment.addSegment(esvg::render::Point(vec2(tmpColor->m_viewPort.second.x(), tmpColor->m_viewPort.first.y()) ),
			                       esvg::render::Point(tmpColor->m_viewPort.first),
			                       false);
			listSegment.applyMatrix(tmpColor->m_matrix);
			// display the gradient axis
			listSegment.addSegment(esvg::render::Point(tmpColor->m_pos1),
			                       esvg::render::Point(tmpColor->m_pos2),
			                       false);
			/*
				mat2x3 m_matrix;
				etk::Pair<vec2, vec2> m_viewPort;
				vec2 m_pos1;
				vec2 m_pos2;
			*/
			addDebugSegment(listSegment);
		}
	#endif
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
			etk::Vector<esvg::render::Segment> availlableSegmentPixel;
			for (auto &it : _listSegment.m_data) {
				if (    it.p0.y() * m_factor <= float(yyy+1)
				     && it.p1.y() * m_factor >= float(yyy)) {
					availlableSegmentPixel.pushBack(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + 0.5f;
			etk::Vector<esvg::render::Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    it.p0.y() * m_factor <= subSamplingCenterPos
				     && it.p1.y() * m_factor >= subSamplingCenterPos ) {
					availlableSegment.pushBack(it);
				}
			}
			// x position, angle
			etk::Vector<etk::Pair<float, float>> listPosition;
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
			etk::Vector<esvg::render::Segment> availlableSegmentPixel;
			for (auto &it : _listSegment.m_data) {
				if (    (    it.p0.x() * m_factor <= float(xxx+1)
				          && it.p1.x() * m_factor >= float(xxx) )
				     || (    it.p0.x() * m_factor >= float(xxx+1)
				          && it.p1.x() * m_factor <= float(xxx) ) ) {
					availlableSegmentPixel.pushBack(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = xxx + 0.5f;
			etk::Vector<esvg::render::Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    (    it.p0.x() * m_factor <= subSamplingCenterPos
				          && it.p1.x() * m_factor >= subSamplingCenterPos)
				     || (    it.p0.x() * m_factor >= subSamplingCenterPos
				          && it.p1.x() * m_factor <= subSamplingCenterPos) ) {
					availlableSegment.pushBack(it);
				}
			}
			// x position, angle
			etk::Vector<etk::Pair<float, float>> listPosition;
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


void esvg::Renderer::writePPM(const etk::String& _fileName) {
	if (m_buffer.size() == 0) {
		return;
	}
	etk::FSNode tmpFile(_fileName);
	if(tmpFile.fileOpenWrite() == false) {
		ESVG_ERROR("Can not find the file name=\"" << tmpFile << "\"");
		return;
	}
	int32_t sizeX = m_size.x();
	int32_t sizeY = m_size.y();
	#if DEBUG
		sizeX *= m_factor;
		sizeY *= m_factor;
	#endif
	ESVG_DEBUG("Generate ppm : " << m_size << " debug size=" << ivec2(sizeX,sizeY));
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
void esvg::Renderer::writeBMP(const etk::String& _fileName) {
	if (m_buffer.size() == 0) {
		return;
	}
	etk::FSNode tmpFile(_fileName);
	
	if(tmpFile.fileOpenWrite() == false) {
		ESVG_ERROR("Can not find the file name=\"" << tmpFile << "\"");
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
	infoHeader.biLCSColorSpace = 0x73524742; // "Win "
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

etk::Vector<etk::Color<float,4>> esvg::Renderer::getData() {
	return m_buffer;
}




void esvg::Renderer::setInterpolationRecurtionMax(int32_t _value) {
	m_interpolationRecurtionMax = etk::avg(1, _value, 200);
}

int32_t esvg::Renderer::getInterpolationRecurtionMax() const {
	return m_interpolationRecurtionMax;
}

void esvg::Renderer::setInterpolationThreshold(float _value) {
	m_interpolationThreshold = etk::avg(0.0f, _value, 20000.0f);
}

float esvg::Renderer::getInterpolationThreshold() const {
	return m_interpolationThreshold;
}

void esvg::Renderer::setNumberSubScanLine(int32_t _value) {
	m_nbSubScanLine = etk::avg(1, _value, 200);
}

int32_t esvg::Renderer::getNumberSubScanLine() const {
	return m_nbSubScanLine;
}



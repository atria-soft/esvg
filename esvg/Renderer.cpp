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

esvg::Renderer::Renderer(const ivec2& _size, bool _visualDebug) :
#ifdef DEBUG
  m_visualDebug(_visualDebug),
  m_factor(1),
#endif
  m_interpolationRecurtionMax(10),
  m_interpolationThreshold(0.25f),
  m_nbSubScanLine(8) {
	if (m_visualDebug == true) {
		m_factor = 10;
	}
	setSize(_size);
}

esvg::Renderer::~Renderer() {
	m_buffer.clear();
	m_size = ivec2(0,0);
}

etk::Color<float,4> esvg::Renderer::mergeColor(etk::Color<float,4> _base, const etk::Color<float,4>& _integration) {
	if (_integration.a() == 0.0f) {
		return _base;
	}
	etk::Color<float,4> tmpColor(_integration.r()*_integration.a(),
	                             _integration.g()*_integration.a(),
	                             _integration.b()*_integration.a(),
	                             _integration.a());
	// Blend over
	float tmpA = std::min(1.0f, (_base.a() + _integration.a()));
	_base *= (1.0f - _integration.a());
	_base += tmpColor;
	_base.setA(tmpA);
	return _base;
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
						etk::Color<float,4> tmpColor = _colorStroke * valueStroke * _opacity;
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
						etk::Color<float,4> tmpColor = _colorFill * valueFill * _opacity;
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
					etk::Color<float,4> intermediateColorFill = _colorFill*valueFill;
					etk::Color<float,4> intermediateColorStroke = _colorStroke*valueStroke;
					etk::Color<float,4> intermediateColor = mergeColor(intermediateColorFill, intermediateColorStroke) * _opacity;
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
				     && it.p1.y() * m_factor >= subSamplingCenterPos) {
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
				m_buffer[(dynamicSize.x()*yyy + int32_t(xpos))] = etk::color::blue;
			}
		}
	}
#endif


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
		#if DEBUG
			sizeX *= m_factor;
			sizeY *= m_factor;
		#endif
		SVG_DEBUG("Generate ppm : " << m_size << " debug size=" << ivec2(sizeX,sizeY));
		fprintf(fd, "P6 %d %d 255 ", sizeX, sizeY);
		for (int32_t iii=0 ; iii<sizeX*sizeY; iii++) {
			etk::Color<uint8_t,3> tmp = m_buffer[iii];
			fwrite(&tmp, 1, 3, fd);
		}
		fclose(fd);
	}
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


uint8_t* esvg::Renderer::getDataPointer() {
	return nullptr; //&m_buffer[0];
};


uint32_t esvg::Renderer::getDataSize() const {
	return m_buffer.size();
};

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



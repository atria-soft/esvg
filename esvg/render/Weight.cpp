/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Weight.h>
#include <esvg/debug.h>

#undef __class__
#define __class__	"render::Weight"


esvg::render::Weight::Weight() {
	
}

esvg::render::Weight::Weight(const ivec2& _size):
  m_size(_size) {
	resize(_size);
}

esvg::render::Weight::~Weight() {
	
}

void esvg::render::Weight::resize(const ivec2& _size) {
	m_size = _size;
	float tmp(0);
	m_data.resize(m_size.x()*m_size.y(), tmp);
	if ((uint32_t)m_size.x()*m_size.y() > m_data.size()) {
		SVG_WARNING("Wrong weigth buffer size ...");
		return;
	}
}

const ivec2& esvg::render::Weight::getSize() const {
	return m_size;
}

int32_t esvg::render::Weight::getWidth() const {
	return m_size.x();
}

int32_t esvg::render::Weight::getHeight() const {
	return m_size.y();
}

void esvg::render::Weight::clear(float _fill) {
	for (int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
		m_data[iii] = _fill;
	}
}

float esvg::render::Weight::get(const ivec2& _pos) const {
	if (    _pos.x()>0 && _pos.x()<m_size.x()
	     && _pos.y()>0 && _pos.y()<m_size.y()) {
		return m_data[_pos.x()+_pos.y()*m_size.x()];
	}
	return 0;
}

void esvg::render::Weight::set(const ivec2& _pos, float _newColor) {
	if (    _pos.x()>=0 && _pos.x()<m_size.x()
	     && _pos.y()>=0 && _pos.y()<m_size.y()) {
		m_data[_pos.x()+_pos.y()*m_size.x()] = _newColor;
	}
}

void esvg::render::Weight::set(int32_t _posY, const esvg::render::Scanline& _data) {
	if (    _posY>=0
	     && _posY<m_size.y()) {
		for (size_t xxx=0; xxx<m_size.x(); ++xxx) {
			m_data[xxx+_posY*m_size.x()] = _data.get(xxx);
		}
	}
}

void esvg::render::Weight::append(int32_t _posY, const esvg::render::Scanline& _data) {
	if (    _posY>=0
	     && _posY<m_size.y()) {
		for (size_t xxx=0; xxx<m_size.x(); ++xxx) {
			m_data[xxx+_posY*m_size.x()] += _data.get(xxx);
		}
	}
}

bool sortXPosFunction(const std::pair<float,float>& _e1, const std::pair<float,float>& _e2) {
	return _e1.first < _e2.first;
}


void esvg::render::Weight::generate(ivec2 _size, int32_t _subSamplingCount, const esvg::render::SegmentList& _listSegment) {
	resize(_size);
	// for each lines:
	for (int32_t yyy=0; yyy<_size.y(); ++yyy) {
		// Reduce the number of lines in the subsampling parsing:
		std::vector<Segment> availlableSegmentPixel;
		for (auto &it : _listSegment.m_data) {
			if (    it.p0.y() <= float(yyy+1)
			     && it.p1.y() >= float(yyy)) {
				availlableSegmentPixel.push_back(it);
			}
		}
		// This represent the pondaration on the subSampling
		float deltaSize = 1.0f/_subSamplingCount;
		for (int32_t kkk=0; kkk<_subSamplingCount ; ++kkk) {
			Scanline scanline(_size.x());
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + deltaSize*0.5f + deltaSize*kkk;
			std::vector<Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    it.p0.y() <= subSamplingCenterPos
				     && it.p1.y() >= subSamplingCenterPos) {
					availlableSegment.push_back(it);
				}
			}
			// x position, angle
			std::vector<std::pair<float, float>> listPosition;
			for (auto &it : availlableSegment) {
				vec2 delta = it.p0 - it.p1;
				// x = coefficent*y+bbb;
				float coefficient = delta.x()/delta.y();
				float bbb = it.p0.x() - coefficient*it.p0.y();
				float xpos = coefficient * subSamplingCenterPos + bbb;
				listPosition.push_back(std::pair<float,float>(xpos, it.direction));
			}
			// now we order position of the xPosition:
			std::sort(listPosition.begin(), listPosition.end(), sortXPosFunction);
			// move through all element in the point:
			float lastState = 0.0f;
			float currentValue = 0.0f;
			int32_t lastPos = -1;
			int32_t currentPos = -1;
			float lastX = 0.0f;
			// *      |                \---------------/              |
			// * current pos
			//                         * pos ...
			// TODO : Code the Odd/even and non-zero ...
			for (auto &it : listPosition) {
				if (currentPos != int32_t(it.first)) {
					// fill to the new pos -1:
					float endValue = std::min(1.0f,std::abs(lastState)) * deltaSize;
					for (int32_t iii=currentPos+1; iii<int32_t(it.first); ++iii) {
						scanline.set(iii, endValue);
					}
					currentPos = int32_t(it.first);
					currentValue = endValue;
				}
				float oldState = lastState;
				lastState += it.second;
				if (oldState == 0.0f) {
					// nothing to draw before ...
					float ratio = 1.0f - (it.first - float(int32_t(it.first)));
					currentValue += ratio * deltaSize;
				} else if (lastState == 0.0f) {
					// something new to draw ...
					float ratio = 1.0f - (it.first - float(int32_t(it.first)));
					currentValue -= ratio * deltaSize;
				} else {
					// nothing to do ...
				}
				
				if (currentPos == int32_t(it.first)) {
					scanline.set(currentPos, currentValue);
				}
			}
			append(yyy, scanline);
		}
	}
}

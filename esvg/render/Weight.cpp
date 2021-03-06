/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Weight.hpp>
#include <esvg/debug.hpp>
#include <etk/algorithm.hpp>

esvg::render::Weight::Weight() :
  m_size(0,0)  {
	
}

esvg::render::Weight::Weight(const ivec2& _size) :
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
		ESVG_WARNING("Wrong weigth buffer size ...");
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
	if (    _pos.x()>=0 && _pos.x()<m_size.x()
	     && _pos.y()>=0 && _pos.y()<m_size.y()) {
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
		for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
			m_data[xxx+_posY*m_size.x()] = _data.get(xxx);
		}
	}
}

void esvg::render::Weight::append(int32_t _posY, const esvg::render::Scanline& _data) {
	if (    _posY>=0
	     && _posY<m_size.y()) {
		for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
			m_data[xxx+_posY*m_size.x()] += _data.get(xxx);
		}
	}
}

bool sortXPosFunction(const etk::Pair<float,int32_t>& _e1, const etk::Pair<float,int32_t>& _e2) {
	return _e1.first < _e2.first;
}


void esvg::render::Weight::generate(ivec2 _size, int32_t _subSamplingCount, const esvg::render::SegmentList& _listSegment) {
	resize(_size);
	// for each lines:
	for (int32_t yyy=0; yyy<_size.y(); ++yyy) {
		ESVG_VERBOSE("Weighting ... " << yyy << " / " << _size.y());
		// Reduce the number of lines in the subsampling parsing:
		etk::Vector<Segment> availlableSegmentPixel;
		for (auto &it : _listSegment.m_data) {
			if (    it.p0.y() < float(yyy+1)
			     && it.p1.y() > float(yyy)) {
				availlableSegmentPixel.pushBack(it);
			}
		}
		if (availlableSegmentPixel.size() == 0) {
			continue;
		}
		ESVG_VERBOSE("          Find Basic segments " << availlableSegmentPixel.size());
		// This represent the pondaration on the subSampling
		float deltaSize = 1.0f/_subSamplingCount;
		for (int32_t kkk=0; kkk<_subSamplingCount ; ++kkk) {
			ESVG_VERBOSE("    Scanline ... " << kkk << " / " << _subSamplingCount);
			Scanline scanline(_size.x());
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + deltaSize*0.5f + deltaSize*kkk;
			etk::Vector<Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    it.p0.y() <= subSamplingCenterPos
				     && it.p1.y() > subSamplingCenterPos) {
					// check if we not get 2 identical lines:
					if (    availlableSegment.size() > 0
					     && availlableSegment.back().p1 == it.p0
					     && availlableSegment.back().direction == it.direction) {
						// we not add this point in this case to prevent double count of the same point.
					} else {
						availlableSegment.pushBack(it);
					}
				}
			}
			ESVG_VERBOSE("        Availlable Segment " << availlableSegment.size());
			if (availlableSegment.size() == 0) {
				continue;
			}
			for (auto &it : availlableSegment) {
				ESVG_VERBOSE("        Availlable Segment " << it.p0 << " -> " << it.p1 << " dir=" << it.direction);
			}
			// x position, angle
			etk::Vector<etk::Pair<float, int32_t>> listPosition;
			for (auto &it : availlableSegment) {
				vec2 delta = it.p0 - it.p1;
				// x = coefficent*y+bbb;
				float coefficient = delta.x()/delta.y();
				float bbb = it.p0.x() - coefficient*it.p0.y();
				float xpos = coefficient * subSamplingCenterPos + bbb;
				listPosition.pushBack(etk::Pair<float,int32_t>(xpos, it.direction));
			}
			ESVG_VERBOSE("        List position " << listPosition.size());
			// now we order position of the xPosition:
			etk::algorithm::quickSort(listPosition, sortXPosFunction);
			// move through all element in the point:
			int32_t lastState = 0;
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
					#if __CPP_VERSION__ >= 2011 && !defined(__TARGET_OS__MacOs) && !defined(__TARGET_OS__IOs)
						float endValue = float(etk::min(1,etk::abs(lastState))) * deltaSize;
					#else
						float endValue = float(etk::min(1,abs(lastState))) * deltaSize;
					#endif
					for (int32_t iii=currentPos+1; iii<int32_t(it.first); ++iii) {
						scanline.set(iii, endValue);
					}
					currentPos = int32_t(it.first);
					currentValue = endValue;
				}
				int32_t oldState = lastState;
				lastState += it.second;
				if (oldState == 0) {
					// nothing to draw before ...
					float ratio = 1.0f - (it.first - float(int32_t(it.first)));
					currentValue += ratio * deltaSize;
				} else if (lastState == 0) {
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
			// if the counter is not at 0 ==> fill if to the end with full value ... 2.0
			if (lastState != 0) {
				// just past the last state to the end of the image ...
				ESVG_ERROR("end of Path whith no end ... " << currentPos << " -> " << _size.x());
				for (int32_t xxx=currentPos; xxx<_size.x(); ++xxx) {
					scanline.set(xxx, 100.0);
				}
			}
			append(yyy, scanline);
		}
	}
}

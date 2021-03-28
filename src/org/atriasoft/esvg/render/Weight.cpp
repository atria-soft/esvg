/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Weight.hpp>
#include <esvg/debug.hpp>
#include <etk/algorithm.hpp>

esvg::render::Weight::Weight() :
  this.size(0,0)  {
	
}

esvg::render::Weight::Weight(const Vector2i& _size) :
  this.size(_size) {
	resize(_size);
}

esvg::render::Weight::~Weight() {
	
}

void esvg::render::Weight::resize(const Vector2i& _size) {
	this.size = _size;
	float tmp(0);
	this.data.resize(this.size.x()*this.size.y(), tmp);
	if ((uint)this.size.x()*this.size.y() > this.data.size()) {
		Log.warning("Wrong weigth buffer size ...");
		return;
	}
}

const Vector2i& esvg::render::Weight::getSize() const {
	return this.size;
}

int esvg::render::Weight::getWidth() const {
	return this.size.x();
}

int esvg::render::Weight::getHeight() const {
	return this.size.y();
}

void esvg::render::Weight::clear(float _fill) {
	for (int iii=0; iii<this.size.x()*this.size.y(); iii++) {
		this.data[iii] = _fill;
	}
}

float esvg::render::Weight::get(const Vector2i& _pos) const {
	if (    _pos.x()>=0 && _pos.x()<this.size.x()
	     && _pos.y()>=0 && _pos.y()<this.size.y()) {
		return this.data[_pos.x()+_pos.y()*this.size.x()];
	}
	return 0;
}

void esvg::render::Weight::set(const Vector2i& _pos, float _newColor) {
	if (    _pos.x()>=0 && _pos.x()<this.size.x()
	     && _pos.y()>=0 && _pos.y()<this.size.y()) {
		this.data[_pos.x()+_pos.y()*this.size.x()] = _newColor;
	}
}

void esvg::render::Weight::set(int _posY, const esvg::render::Scanline& _data) {
	if (    _posY>=0
	     && _posY<this.size.y()) {
		for (int xxx=0; xxx<this.size.x(); ++xxx) {
			this.data[xxx+_posY*this.size.x()] = _data.get(xxx);
		}
	}
}

void esvg::render::Weight::append(int _posY, const esvg::render::Scanline& _data) {
	if (    _posY>=0
	     && _posY<this.size.y()) {
		for (int xxx=0; xxx<this.size.x(); ++xxx) {
			this.data[xxx+_posY*this.size.x()] += _data.get(xxx);
		}
	}
}

boolean sortXPosFunction(const Pair<float,int>& _e1, const Pair<float,int>& _e2) {
	return _e1.first < _e2.first;
}


void esvg::render::Weight::generate(Vector2i _size, int _subSamplingCount, const esvg::render::SegmentList& _listSegment) {
	resize(_size);
	// for each lines:
	for (int yyy=0; yyy<_size.y(); ++yyy) {
		Log.verbose("Weighting ... " << yyy << " / " << _size.y());
		// Reduce the number of lines in the subsampling parsing:
		List<Segment> availlableSegmentPixel;
		for (auto &it : _listSegment.this.data) {
			if (    it.p0.y() < float(yyy+1)
			     && it.p1.y() > float(yyy)) {
				availlableSegmentPixel.pushBack(it);
			}
		}
		if (availlableSegmentPixel.size() == 0) {
			continue;
		}
		Log.verbose("          Find Basic segments " << availlableSegmentPixel.size());
		// This represent the pondaration on the subSampling
		float deltaSize = 1.0f/_subSamplingCount;
		for (int kkk=0; kkk<_subSamplingCount ; ++kkk) {
			Log.verbose("    Scanline ... " << kkk << " / " << _subSamplingCount);
			Scanline scanline(_size.x());
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + deltaSize*0.5f + deltaSize*kkk;
			List<Segment> availlableSegment;
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
			Log.verbose("        Availlable Segment " << availlableSegment.size());
			if (availlableSegment.size() == 0) {
				continue;
			}
			for (auto &it : availlableSegment) {
				Log.verbose("        Availlable Segment " << it.p0 << " -> " << it.p1 << " dir=" << it.direction);
			}
			// x position, angle
			List<Pair<float, int>> listPosition;
			for (auto &it : availlableSegment) {
				Vector2f delta = it.p0 - it.p1;
				// x = coefficent*y+bbb;
				float coefficient = delta.x()/delta.y();
				float bbb = it.p0.x() - coefficient*it.p0.y();
				float xpos = coefficient * subSamplingCenterPos + bbb;
				listPosition.pushBack(Pair<float,int>(xpos, it.direction));
			}
			Log.verbose("        List position " << listPosition.size());
			// now we order position of the xPosition:
			etk::algorithm::quickSort(listPosition, sortXPosFunction);
			// move through all element in the point:
			int lastState = 0;
			float currentValue = 0.0f;
			int lastPos = -1;
			int currentPos = -1;
			float lastX = 0.0f;
			// *      |                \---------------/              |
			// * current pos
			//                         * pos ...
			// TODO : Code the Odd/even and non-zero ...
			for (auto &it : listPosition) {
				if (currentPos != int(it.first)) {
					// fill to the new pos -1:
					#if __CPP_VERSION__ >= 2011 && !defined(__TARGET_OS__MacOs) && !defined(__TARGET_OS__IOs)
						float endValue = float(etk::min(1,etk::abs(lastState))) * deltaSize;
					#else
						float endValue = float(etk::min(1,abs(lastState))) * deltaSize;
					#endif
					for (int iii=currentPos+1; iii<int(it.first); ++iii) {
						scanline.set(iii, endValue);
					}
					currentPos = int(it.first);
					currentValue = endValue;
				}
				int oldState = lastState;
				lastState += it.second;
				if (oldState == 0) {
					// nothing to draw before ...
					float ratio = 1.0f - (it.first - float(int(it.first)));
					currentValue += ratio * deltaSize;
				} else if (lastState == 0) {
					// something new to draw ...
					float ratio = 1.0f - (it.first - float(int(it.first)));
					currentValue -= ratio * deltaSize;
				} else {
					// nothing to do ...
				}
				
				if (currentPos == int(it.first)) {
					scanline.set(currentPos, currentValue);
				}
			}
			// if the counter is not at 0 ==> fill if to the end with full value ... 2.0
			if (lastState != 0) {
				// just past the last state to the end of the image ...
				Log.error("end of Path whith no end ... " << currentPos << " -> " << _size.x());
				for (int xxx=currentPos; xxx<_size.x(); ++xxx) {
					scanline.set(xxx, 100.0);
				}
			}
			append(yyy, scanline);
		}
	}
}

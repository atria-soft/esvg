package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.ArraysTools;
import org.atriasoft.etk.util.Pair;

public class Weight {
	private float[][] data = null;
	private Vector2i size;
	
	// constructor :
	public Weight() {
		this.size = Vector2i.ZERO;
	}
	
	public Weight(final Vector2i size) {
		this.size = size;
		resize(size);
	}
	
	public void append(final int posY, final Scanline data) {
		if (posY >= 0 && posY < this.size.y()) {
			for (int xxx = 0; xxx < this.size.x(); ++xxx) {
				this.data[posY][xxx] += data.get(xxx);
			}
		}
	}
	
	public void clear(final float fill) {
		ArraysTools.fill2(this.data, fill);
	}
	
	public void generate(final Vector2i size, final int subSamplingCount, final SegmentList listSegment) {
		resize(size);
		// for each lines:
		for (int yyy = 0; yyy < size.y(); ++yyy) {
			Log.verbose("Weighting ... " + yyy + " / " + size.y());
			// Reduce the number of lines in the subsampling parsing:
			List<Segment> availlableSegmentPixel = new ArrayList<Segment>();
			for (Segment it : listSegment.data) {
				if (it.p0.y() < yyy + 1 && it.p1.y() > (yyy)) {
					availlableSegmentPixel.add(it);
				}
			}
			if (availlableSegmentPixel.size() == 0) {
				continue;
			}
			Log.verbose("          Find Basic segments " + availlableSegmentPixel.size());
			// This represent the pondaration on the subSampling
			float deltaSize = 1.0f / subSamplingCount;
			for (int kkk = 0; kkk < subSamplingCount; ++kkk) {
				Log.verbose("    Scanline ... " + kkk + " / " + subSamplingCount);
				Scanline scanline = new Scanline(size.x());
				//find all the segment that cross the middle of the line of the center of the pixel line:
				float subSamplingCenterPos = yyy + deltaSize * 0.5f + deltaSize * kkk;
				List<Segment> availlableSegment = new ArrayList<>();
				// find in the subList ...
				for (Segment it : availlableSegmentPixel) {
					if (it.p0.y() <= subSamplingCenterPos && it.p1.y() > subSamplingCenterPos) {
						// check if we not get 2 identical lines:
						if (availlableSegment.size() > 0 && availlableSegment.get(availlableSegment.size() - 1).p1 == it.p0
								&& availlableSegment.get(availlableSegment.size() - 1).direction == it.direction) {
							// we not add this point in this case to prevent double count of the same point.
						} else {
							availlableSegment.add(it);
						}
					}
				}
				Log.verbose("        Availlable Segment " + availlableSegment.size());
				if (availlableSegment.size() == 0) {
					continue;
				}
				for (Segment it : availlableSegment) {
					Log.verbose("        Availlable Segment " + it.p0 + " . " + it.p1 + " dir=" + it.direction);
				}
				// x position, angle
				List<Pair<Float, Integer>> listPosition = new ArrayList<>();
				for (Segment it : availlableSegment) {
					Vector2f delta = it.p0.less(it.p1);
					// x = coefficent*y+bbb;
					float coefficient = delta.x() / delta.y();
					float bbb = it.p0.x() - coefficient * it.p0.y();
					float xpos = coefficient * subSamplingCenterPos + bbb;
					listPosition.add(new Pair<Float, Integer>(xpos, it.direction));
				}
				Log.verbose("        List position " + listPosition.size());
				// now we order position of the xPosition:
				Collections.sort(listPosition, (e1, e2) -> ((int) (e1.first - e2.first)));
				
				// move through all element in the point:
				int lastState = 0;
				float currentValue = 0.0f;
				int currentPos = -1;
				// *      |                \---------------/              |
				// * current pos
				//                         * pos ...
				// TODO  Code the Odd/even and non-zero ...
				for (Pair<Float, Integer> it : listPosition) {
					if (currentPos != it.first.intValue()) {
						// fill to the new pos -1:
						float endValue = FMath.min(1.0f, FMath.abs(lastState)) * deltaSize;
						for (int iii = currentPos + 1; iii < it.first.intValue(); ++iii) {
							scanline.set(iii, endValue);
						}
						currentPos = it.first.intValue();
						currentValue = endValue;
					}
					int oldState = lastState;
					lastState += it.second;
					if (oldState == 0) {
						// nothing to draw before ...
						float ratio = 1.0f - (it.first - it.first.intValue());
						currentValue += ratio * deltaSize;
					} else if (lastState == 0) {
						// something new to draw ...
						float ratio = 1.0f - (it.first - it.first.intValue());
						currentValue -= ratio * deltaSize;
					} else {
						// nothing to do ...
					}
					
					if (currentPos == it.first.intValue()) {
						scanline.set(currentPos, currentValue);
					}
				}
				// if the counter is not at 0 ==> fill if to the end with full value ... 2.0
				if (lastState != 0) {
					// just past the last state to the end of the image ...
					Log.error("end of Path whith no end ... " + currentPos + " . " + size.x());
					for (int xxx = currentPos; xxx < size.x(); ++xxx) {
						scanline.set(xxx, 100.0f);
					}
				}
				append(yyy, scanline);
			}
		}
	}
	
	public float get(final Vector2i pos) {
		if (this.data == null) {
			return 0;
		}
		return this.data[pos.y()][pos.x()];
	}
	
	public int getHeight() {
		return this.size.y();
	}
	
	public Vector2i getSize() {
		return this.size;
	}
	
	public int getWidth() {
		return this.size.x();
	}
	
	// -----------------------------------------------
	// -- basic tools :
	// -----------------------------------------------
	public void resize(final Vector2i size) {
		this.size = size;
		this.data = new float[this.size.y()][this.size.x()];
		clear(0);
	}
	
	public void set(final int posY, final Scanline data) {
		if (posY >= 0 && posY < this.size.y()) {
			for (int xxx = 0; xxx < this.size.x(); ++xxx) {
				this.data[posY][xxx] = data.get(xxx);
			}
		}
	}
	
	public void set(final Vector2i pos, final float newColor) {
		this.data[pos.y()][pos.x()] = newColor;
	}
	
}

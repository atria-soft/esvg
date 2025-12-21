package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.IntStream;

import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.ArraysTools;
import org.atriasoft.etk.util.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Weight {
	static final Logger LOGGER = LoggerFactory.getLogger(Weight.class);
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

	public void fusion(final Weight redered, final int offsetXXX, final int offsetYYY) {
		for (int yyy = 0; yyy < redered.getHeight(); yyy++) {
			for (int xxx = 0; xxx < redered.getWidth(); xxx++) {
				this.data[offsetYYY + yyy][offsetXXX + xxx] = FMath.avg(0.0f,
						this.data[offsetYYY + yyy][offsetXXX + xxx] + redered.get(xxx, yyy), 1.0f);
			}
		}

	}

	public void generate(final Vector2i size, final int subSamplingCount, final SegmentList listSegment) {
		resize(size);

		final int sizeX = size.x();
		final int sizeY = size.y();
		final float deltaSize = 1.0f / subSamplingCount;

		// OPTIMIZATION: Parallel processing of scanlines
		IntStream.range(0, sizeY).parallel().forEach(yyy -> {
			// Thread-local accumulator for this row
			final float[] rowData = new float[sizeX];

			// Reduce the number of lines in the subsampling parsing:
			final List<Segment> availlableSegmentPixel = new ArrayList<>();
			for (final Segment it : listSegment.data) {
				if (it.p0.y() < yyy + 1 && it.p1.y() > (yyy)) {
					availlableSegmentPixel.add(it);
				}
			}
			if (availlableSegmentPixel.isEmpty()) {
				return; // continue in lambda
			}

			for (int kkk = 0; kkk < subSamplingCount; ++kkk) {
				//find all the segment that cross the middle of the line of the center of the pixel line:
				final float subSamplingCenterPos = yyy + deltaSize * 0.5f + deltaSize * kkk;
				final List<Segment> availlableSegment = new ArrayList<>();
				// find in the subList ...
				for (final Segment it : availlableSegmentPixel) {
					if (it.p0.y() <= subSamplingCenterPos && it.p1.y() > subSamplingCenterPos) {
						// check if we not get 2 identical lines:
						if (availlableSegment.size() > 0
								&& availlableSegment.get(availlableSegment.size() - 1).p1 == it.p0
								&& availlableSegment.get(availlableSegment.size() - 1).direction == it.direction) {
							// we not add this point in this case to prevent double count of the same point.
						} else {
							availlableSegment.add(it);
						}
					}
				}
				if (availlableSegment.isEmpty()) {
					continue;
				}

				// x position, direction
				final List<Pair<Float, Integer>> listPosition = new ArrayList<>();
				for (final Segment it : availlableSegment) {
					final Vector2f delta = it.p0.less(it.p1);
					// x = coefficient*y+bbb;
					final float coefficient = delta.x() / delta.y();
					final float bbb = it.p0.x() - coefficient * it.p0.y();
					final float xpos = coefficient * subSamplingCenterPos + bbb;
					listPosition.add(new Pair<>(xpos, it.direction));
				}

				// now we order position of the xPosition:
				Collections.sort(listPosition, (e1, e2) -> Float.compare(e1.first, e2.first));

				// move through all element in the point:
				int lastState = 0;
				float currentValue = 0.0f;
				int currentPos = -1;

				for (final Pair<Float, Integer> it : listPosition) {
					if (currentPos != it.first.intValue()) {
						// fill to the new pos -1:
						final float endValue = FMath.min(1.0f, FMath.abs(lastState)) * deltaSize;
						for (int iii = currentPos + 1; iii < it.first.intValue(); ++iii) {
							if (iii >= 0 && iii < sizeX) {
								rowData[iii] += endValue;
							}
						}
						currentPos = it.first.intValue();
						currentValue = endValue;
					}
					final int oldState = lastState;
					lastState += it.second;
					if (oldState == 0) {
						// nothing to draw before ...
						final float ratio = 1.0f - (it.first - it.first.intValue());
						currentValue += ratio * deltaSize;
					} else if (lastState == 0) {
						// something new to draw ...
						final float ratio = 1.0f - (it.first - it.first.intValue());
						currentValue -= ratio * deltaSize;
					}

					if (currentPos == it.first.intValue() && currentPos >= 0 && currentPos < sizeX) {
						rowData[currentPos] += currentValue;
					}
				}
				// if the counter is not at 0 ==> fill if to the end with full value ... 2.0
				if (lastState != 0) {
					// just past the last state to the end of the image ...
					LOGGER.error("end of Path with no end ... " + currentPos + " . " + sizeX);
					for (int xxx = currentPos; xxx < sizeX; ++xxx) {
						if (xxx >= 0) {
							rowData[xxx] += 100.0f;
						}
					}
				}
			}

			// Copy row data to main buffer (each row is independent, no sync needed)
			System.arraycopy(rowData, 0, this.data[yyy], 0, sizeX);
		});
	}

	public float get(final int xxx, final int yyy) {
		if (this.data == null) {
			return 0;
		}
		return this.data[yyy][xxx];
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
		if (this.size.x() <= 0) {
			LOGGER.error("Error in the Weight size : " + this.size);
			this.size = this.size.withX(1);
		}
		if (this.size.y() <= 0) {
			LOGGER.error("Error in the Weight size : " + this.size);
			this.size = this.size.withY(1);
		}
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

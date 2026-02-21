package org.atriasoft.esvg.render;

import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.ArraysTools;
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

	public void clear(final float fill) {
		ArraysTools.fill2(this.data, fill);
	}

	public void fusion(final Weight rendered, final int offsetXXX, final int offsetYYY) {
		for (int yyy = 0; yyy < rendered.getHeight(); yyy++) {
			for (int xxx = 0; xxx < rendered.getWidth(); xxx++) {
				this.data[offsetYYY + yyy][offsetXXX + xxx] = FMath.avg(0.0f,
						this.data[offsetYYY + yyy][offsetXXX + xxx] + rendered.get(xxx, yyy), 1.0f);
			}
		}
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
			LOGGER.error("Error in the Weight size: {}", this.size);
			this.size = this.size.withX(1);
		}
		if (this.size.y() <= 0) {
			LOGGER.error("Error in the Weight size: {}", this.size);
			this.size = this.size.withY(1);
		}
		this.data = new float[this.size.y()][this.size.x()];
		clear(0);
	}

	public void set(final Vector2i pos, final float newColor) {
		this.data[pos.y()][pos.x()] = newColor;
	}

}

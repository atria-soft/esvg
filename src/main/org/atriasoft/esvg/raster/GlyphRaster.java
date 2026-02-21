package org.atriasoft.esvg.raster;

import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.ArraysTools;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 2D grayscale raster for rendered glyphs.
 * Each cell holds a float value between 0.0 (transparent) and 1.0 (opaque).
 */
public class GlyphRaster {
	private static final Logger LOGGER = LoggerFactory.getLogger(GlyphRaster.class);
	private float[][] data = null;
	private Vector2i size;

	public GlyphRaster() {
		this.size = Vector2i.ZERO;
	}

	public GlyphRaster(final Vector2i size) {
		this.size = size;
		resize(size);
	}

	public void clear(final float fill) {
		ArraysTools.fill2(this.data, fill);
	}

	/**
	 * Composite another raster onto this one at the given offset.
	 * Values are clamped to [0.0, 1.0].
	 */
	public void fusion(final GlyphRaster rendered, final int offsetX, final int offsetY) {
		for (int y = 0; y < rendered.getHeight(); y++) {
			for (int x = 0; x < rendered.getWidth(); x++) {
				this.data[offsetY + y][offsetX + x] = FMath.avg(0.0f,
						this.data[offsetY + y][offsetX + x] + rendered.get(x, y), 1.0f);
			}
		}
	}

	public float get(final int x, final int y) {
		if (this.data == null) {
			return 0;
		}
		return this.data[y][x];
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

	public void resize(final Vector2i size) {
		this.size = size;
		if (this.size.x() <= 0) {
			LOGGER.error("Error in the GlyphRaster size: {}", this.size);
			this.size = this.size.withX(1);
		}
		if (this.size.y() <= 0) {
			LOGGER.error("Error in the GlyphRaster size: {}", this.size);
			this.size = this.size.withY(1);
		}
		this.data = new float[this.size.y()][this.size.x()];
		clear(0);
	}

	public void set(final Vector2i pos, final float newColor) {
		this.data[pos.y()][pos.x()] = newColor;
	}
}

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

	/** Create an empty raster with zero size. */
	public GlyphRaster() {
		this.size = Vector2i.ZERO;
	}

	/**
	 * Create a raster with the given size, initialized to 0.0 (transparent).
	 * @param size the raster dimensions (width x height)
	 */
	public GlyphRaster(final Vector2i size) {
		this.size = size;
		resize(size);
	}

	/**
	 * Fill the entire raster with a uniform value.
	 * @param fill the value to fill with (typically 0.0 or 1.0)
	 */
	public void clear(final float fill) {
		ArraysTools.fill2(this.data, fill);
	}

	/**
	 * Composite another raster onto this one at the given offset.
	 * Values are clamped to [0.0, 1.0]. Pixels that fall outside
	 * this raster's bounds are silently ignored.
	 * @param rendered the source raster to composite
	 * @param offsetX the horizontal offset in this raster
	 * @param offsetY the vertical offset in this raster
	 */
	public void fusion(final GlyphRaster rendered, final int offsetX, final int offsetY) {
		final int maxY = Math.min(rendered.getHeight(), this.size.y() - offsetY);
		final int maxX = Math.min(rendered.getWidth(), this.size.x() - offsetX);
		for (int y = 0; y < maxY; y++) {
			for (int x = 0; x < maxX; x++) {
				this.data[offsetY + y][offsetX + x] = FMath.avg(0.0f,
						this.data[offsetY + y][offsetX + x] + rendered.get(x, y), 1.0f);
			}
		}
	}

	/**
	 * Get the pixel value at the given coordinates.
	 * @param x the horizontal coordinate
	 * @param y the vertical coordinate
	 * @return the pixel value, or 0.0 if the raster is not allocated
	 */
	public float get(final int x, final int y) {
		if (this.data == null) {
			return 0;
		}
		return this.data[y][x];
	}

	/**
	 * Get the pixel value at the given position.
	 * @param pos the position vector (x, y)
	 * @return the pixel value, or 0.0 if the raster is not allocated
	 */
	public float get(final Vector2i pos) {
		if (this.data == null) {
			return 0;
		}
		return this.data[pos.y()][pos.x()];
	}

	/** Get the raster height in pixels. */
	public int getHeight() {
		return this.size.y();
	}

	/** Get the raster dimensions. */
	public Vector2i getSize() {
		return this.size;
	}

	/** Get the raster width in pixels. */
	public int getWidth() {
		return this.size.x();
	}

	/**
	 * Resize the raster, reallocating the internal buffer.
	 * The minimum size is clamped to 1x1. Contents are cleared to 0.0.
	 * @param size the new raster dimensions
	 */
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

	/**
	 * Set the pixel value at the given position.
	 * @param pos the position vector (x, y)
	 * @param newColor the new pixel value
	 */
	public void set(final Vector2i pos, final float newColor) {
		if (this.data == null) {
			return;
		}
		this.data[pos.y()][pos.x()] = newColor;
	}
}

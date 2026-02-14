package org.atriasoft.esvg.render;

import java.awt.image.BufferedImage;

import org.atriasoft.etk.Color;
import org.atriasoft.etk.math.Vector2i;

/**
 * Internal float RGBA buffer used during SVG rendering.
 * Uses Porter-Duff "over" compositing for alpha blending.
 * Converts to standard {@link BufferedImage} for output.
 */
public class SvgRenderBuffer {
	private final float[] buffer;
	private final int width;
	private final int height;

	public SvgRenderBuffer(final int width, final int height) {
		this.width = width;
		this.height = height;
		this.buffer = new float[width * height * 4];
	}

	public SvgRenderBuffer(final Vector2i size) {
		this(size.x(), size.y());
	}

	public int getWidth() {
		return this.width;
	}

	public int getHeight() {
		return this.height;
	}

	public float getRFloat(final int x, final int y) {
		return this.buffer[(y * this.width + x) * 4];
	}

	public float getGFloat(final int x, final int y) {
		return this.buffer[(y * this.width + x) * 4 + 1];
	}

	public float getBFloat(final int x, final int y) {
		return this.buffer[(y * this.width + x) * 4 + 2];
	}

	public float getAFloat(final int x, final int y) {
		return this.buffer[(y * this.width + x) * 4 + 3];
	}

	public void setColor(final int x, final int y, final Color color) {
		final int idx = (y * this.width + x) * 4;
		this.buffer[idx] = color.r();
		this.buffer[idx + 1] = color.g();
		this.buffer[idx + 2] = color.b();
		this.buffer[idx + 3] = color.a();
	}

	public void setColorFloat(final int x, final int y, final float r, final float g, final float b, final float a) {
		final int idx = (y * this.width + x) * 4;
		this.buffer[idx] = r;
		this.buffer[idx + 1] = g;
		this.buffer[idx + 2] = b;
		this.buffer[idx + 3] = a;
	}

	/**
	 * Porter-Duff "over" compositing.
	 * Blends the integration color over the existing pixel at (x, y).
	 */
	public void mergeColor(final int xxx, final int yyy, final Color integration) {
		if (integration.a() == 0.0f) {
			return;
		}
		final int idx = (yyy * this.width + xxx) * 4;
		final float baseA = this.buffer[idx + 3];

		final float r;
		final float g;
		final float b;
		final float a;
		if (baseA == 0.0f) {
			r = integration.r();
			g = integration.g();
			b = integration.b();
			a = integration.a();
		} else {
			final float baseR = this.buffer[idx];
			final float baseG = this.buffer[idx + 1];
			final float baseB = this.buffer[idx + 2];
			r = (integration.a() * integration.r() + baseA * (1.0f - integration.a()) * baseR);
			g = (integration.a() * integration.g() + baseA * (1.0f - integration.a()) * baseG);
			b = (integration.a() * integration.b() + baseA * (1.0f - integration.a()) * baseB);
			a = (integration.a() + baseA * (1.0f - integration.a()));
			if (a != 0.0f) {
				final float reverse = 1.0f / a;
				this.buffer[idx] = r * reverse;
				this.buffer[idx + 1] = g * reverse;
				this.buffer[idx + 2] = b * reverse;
				this.buffer[idx + 3] = a;
				return;
			}
		}
		this.buffer[idx] = r;
		this.buffer[idx + 1] = g;
		this.buffer[idx + 2] = b;
		this.buffer[idx + 3] = a;
	}

	/**
	 * Converts this float RGBA buffer to a standard Java {@link BufferedImage}.
	 */
	public BufferedImage toBufferedImage() {
		final BufferedImage out = new BufferedImage(this.width, this.height, BufferedImage.TYPE_INT_ARGB);
		for (int yyy = 0; yyy < this.height; yyy++) {
			for (int xxx = 0; xxx < this.width; xxx++) {
				final int idx = (yyy * this.width + xxx) * 4;
				final int r = Math.round(this.buffer[idx] * 255) & 0xFF;
				final int g = Math.round(this.buffer[idx + 1] * 255) & 0xFF;
				final int b = Math.round(this.buffer[idx + 2] * 255) & 0xFF;
				final int a = Math.round(this.buffer[idx + 3] * 255) & 0xFF;
				out.setRGB(xxx, yyy, (a << 24) | (r << 16) | (g << 8) | b);
			}
		}
		return out;
	}
}

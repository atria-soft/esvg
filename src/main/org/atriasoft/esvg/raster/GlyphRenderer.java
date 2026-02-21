package org.atriasoft.esvg.raster;

import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.awt.image.Raster;

import org.atriasoft.esvg.SvgFont;
import org.atriasoft.esvg.font.Glyph;
import org.atriasoft.etk.math.Vector2i;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Renders SVG font glyphs to {@link GlyphRaster} using Java2D.
 * Glyphs are rasterized as grayscale anti-aliased shapes.
 */
public final class GlyphRenderer {
	private static final Logger LOGGER = LoggerFactory.getLogger(GlyphRenderer.class);

	/**
	 * Render a single glyph to a grayscale raster.
	 * @param font the SVG font containing the glyph
	 * @param unicodeValue the Unicode code point to render
	 * @param fontSize the requested font size in pixels
	 * @return the rendered raster, or null if the glyph has no shape
	 */
	public static GlyphRaster renderGlyph(final SvgFont font, final int unicodeValue, final int fontSize) {
		final int realSize = font.calculateFontRealHeight(fontSize);
		final Glyph glyph = font.getGlyph(unicodeValue);
		if (glyph == null) {
			return null;
		}
		final Shape shape = glyph.getShape();
		if (shape == null) {
			return null;
		}
		final float scale = (float) realSize / font.getUnitsPerEm();
		final Vector2i renderSize = font.calculateWidthRendering(unicodeValue, fontSize);
		final int w = Math.max(1, renderSize.x());
		final int h = Math.max(1, renderSize.y());

		final BufferedImage image = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_GRAY);
		final Graphics2D g2d = image.createGraphics();
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.setColor(java.awt.Color.WHITE);
		final AffineTransform tx = new AffineTransform();
		tx.scale(scale, scale);
		tx.translate(0, -font.getDescent());
		g2d.setTransform(tx);
		g2d.fill(shape);
		g2d.dispose();

		final GlyphRaster raster = new GlyphRaster(new Vector2i(w, h));
		final Raster imageRaster = image.getRaster();
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				raster.set(new Vector2i(x, y), imageRaster.getSample(x, y, 0) / 255.0f);
			}
		}
		return raster;
	}

	/**
	 * Render a text string to a grayscale raster.
	 * @param font the SVG font to use
	 * @param data the text to render
	 * @param fontSize the requested font size in pixels
	 * @param withKerning true to apply kerning adjustments
	 * @return the rendered raster
	 */
	public static GlyphRaster renderString(final SvgFont font, final String data, final int fontSize,
			final boolean withKerning) {
		final int widthOut = font.calculateWidth(data, fontSize, withKerning);
		final int realSize = font.calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / font.getUnitsPerEm();

		final GlyphRaster result = new GlyphRaster(new Vector2i(Math.max(1, widthOut), realSize));

		float offsetWriting = 0;
		int lastValue = 0;
		for (final char uVal : data.toCharArray()) {
			final Glyph glyph = font.getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				LOGGER.debug("    ==> kerning offset = {}", (glyph.getKerning(lastValue) * scale));
				lastValue = uVal;
			}

			final float advanceX = glyph.getHorizAdvX() * scale;

			final Shape shape = glyph.getShape();
			if (shape != null) {
				final GlyphRaster rendered = renderGlyph(font, uVal, fontSize);
				if (rendered != null) {
					result.fusion(rendered, (int) offsetWriting, 0);
				}
			}
			offsetWriting += advanceX;
		}
		return result;
	}

	private GlyphRenderer() {}
}

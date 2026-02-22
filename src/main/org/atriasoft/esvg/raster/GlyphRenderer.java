package org.atriasoft.esvg.raster;

import java.awt.BasicStroke;
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
	 * Shear factor for synthetic italic (~12 degrees).
	 * Positive value: at py=0 (top) no shift, at py=height bottom shifts right.
	 * Visually: top of glyph leans right (standard italic).
	 */
	private static final double ITALIC_SHEAR = Math.tan(Math.toRadians(12));

	/**
	 * Render a single glyph to a grayscale raster.
	 * @param font the SVG font containing the glyph
	 * @param unicodeValue the Unicode code point to render
	 * @param fontSize the requested font size in pixels
	 * @return the rendered raster, or null if the glyph has no shape
	 */
	public static GlyphRaster renderGlyph(final SvgFont font, final int unicodeValue, final int fontSize) {
		return renderGlyph(font, unicodeValue, fontSize, false, false);
	}

	/**
	 * Render a single glyph to a grayscale raster with optional synthetic bold/italic.
	 * <p>
	 * Synthetic bold is achieved by stroking the glyph outline in addition to filling it.
	 * Synthetic italic is achieved by applying a horizontal shear transform (~12 degrees).
	 * @param font the SVG font containing the glyph
	 * @param unicodeValue the Unicode code point to render
	 * @param fontSize the requested font size in pixels
	 * @param syntheticBold true to apply synthetic bold (stroke + fill)
	 * @param syntheticItalic true to apply synthetic italic (shear transform)
	 * @return the rendered raster, or null if the glyph has no shape
	 */
	public static GlyphRaster renderGlyph(final SvgFont font, final int unicodeValue, final int fontSize,
			final boolean syntheticBold, final boolean syntheticItalic) {
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
		// Extra width for synthetic bold stroke and italic shear
		final int boldExtra = syntheticBold ? Math.max(1, (int) Math.ceil(fontSize * 0.06f)) : 0;
		final int italicExtra = syntheticItalic ? (int) Math.ceil(realSize * Math.tan(Math.toRadians(12))) : 0;
		final int width = Math.max(1, renderSize.x() + boldExtra + italicExtra);
		final int height = Math.max(1, renderSize.y());
		// Offset for glyphs that extend left of the origin
		final float leftOverhang = font.getGlyphLeftOverhang(unicodeValue);

		final BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_GRAY);
		final Graphics2D g2d = image.createGraphics();
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.setColor(java.awt.Color.WHITE);
		// Transform from font coordinates to pixel coordinates.
		// The SVG font path is already Y-down (like screen coords).
		// descent is negative, so translate(0, -descent) moves the origin down.
		//
		// For italic: apply a shear in pixel space AFTER scale+translate.
		// shear(+tan12, 0) → px = px + tan12*py:
		//   At py=0 (top of image = top of glyph): no horizontal shift
		//   At py=height (bottom): shifts right by tan12*height
		// This makes the baseline (bottom) extend right while the top stays → top leans right.
		// The extra width at the bottom is accounted for by italicExtra.
		//
		// AffineTransform concatenation order (last appended = first applied to coords):
		//   Step 1 (innermost): translate(leftOverhang, -descent)  → move to font origin
		//   Step 2: scale(scale, scale)                            → font units to pixels
		//   Step 3 (outermost, if italic): shear                   → lean right
		final AffineTransform tx = new AffineTransform();
		if (syntheticItalic) {
			final double tanVal = Math.tan(Math.toRadians(12));
			tx.shear(tanVal, 0);
		}
		tx.scale(scale, scale);
		tx.translate(leftOverhang, -font.getDescent());
		g2d.setTransform(tx);
		g2d.fill(shape);
		if (syntheticBold) {
			// Stroke width in font units — proportional to font size
			final float strokeWidth = font.getUnitsPerEm() * 0.04f;
			g2d.setStroke(new BasicStroke(strokeWidth, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
			g2d.draw(shape);
		}
		g2d.dispose();

		final GlyphRaster raster = new GlyphRaster(new Vector2i(width, height));
		final Raster imageRaster = image.getRaster();
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
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

	/**
	 * Calculate the raster size that would be produced by renderGlyph().
	 * This allows callers to allocate the correct amount of space before rendering.
	 * @param font the SVG font
	 * @param unicodeValue the Unicode code point
	 * @param fontSize the font size in pixels
	 * @param syntheticBold true if synthetic bold will be applied
	 * @param syntheticItalic true if synthetic italic will be applied
	 * @return the raster dimensions, or null if the glyph has no shape
	 */
	public static Vector2i calculateRasterSize(final SvgFont font, final int unicodeValue, final int fontSize,
			final boolean syntheticBold, final boolean syntheticItalic) {
		final int realSize = font.calculateFontRealHeight(fontSize);
		final Glyph glyph = font.getGlyph(unicodeValue);
		if (glyph == null) {
			return null;
		}
		final Shape shape = glyph.getShape();
		if (shape == null) {
			return null;
		}
		final Vector2i renderSize = font.calculateWidthRendering(unicodeValue, fontSize);
		final int boldExtra = syntheticBold ? Math.max(1, (int) Math.ceil(fontSize * 0.06f)) : 0;
		final int italicExtra = syntheticItalic ? (int) Math.ceil(realSize * Math.tan(Math.toRadians(12))) : 0;
		final int width = Math.max(1, renderSize.x() + boldExtra + italicExtra);
		final int height = Math.max(1, renderSize.y());
		return new Vector2i(width, height);
	}

	private GlyphRenderer() {}
}

package org.atriasoft.esvg;

import java.util.HashMap;
import java.util.Map;

import org.atriasoft.esvg.font.Glyph;
import org.atriasoft.esvg.raster.GlyphRaster;
import org.atriasoft.esvg.raster.GlyphRenderer;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

// https://www.w3.org/TR/SVGTiny12/fonts.html

/*
                             |            |          |            |
                             |            |          |            |
                             |            |          |            |
                      Y      |            |          |            |
                      ^      |------------|          |------------|
                      |
    advance.y:   /->  |
                 |    |
                 |    |
 sizeTex.x /->   |    |         |------------|          |------------|
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |     A      |          |     G      |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           \->   |    |         |------------|          |------------|
        /-->     |    |
        \-->     \->  |
  bearing.y           |
                      |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   X
                           <------------------------> : advance.x
                                <------------> : sizeTexture.x
                           <---> : bearing.x



                                                         _
                              *----------------------*   ^ ==> calculateFontRealHeight(fontSize);
                              |                      |   |   ^ ==> getAscent();
                              |                      |   |   |    _
                              |          /\          |   |   |    ^ ==> Font Height (height of a capital letter) = fontSize
                              |         /  \         |   |   |    |
                              |        /    \        |   |   |    |
                              |       /------\       |   |   |    |
                              |      /        \      |   |   |    |
                              |     /          \     |   |___|____|________________________==> render line
                              |                      |   |                ^
                              |                      |   |                |
                              |                      |   |                |==> getDescent();
                              |                      |   |                |
                              *----------------------*   |                |


*/

/**
 * Represents an SVG font loaded from an SVG font file.
 * <p>
 * Provides font metric calculations, glyph access, and text rendering.
 * Use {@link #load(Uri)} to create instances from SVG font files.
 */
public class SvgFont {
	static final Logger LOGGER = LoggerFactory.getLogger(SvgFont.class);

	// -- Font metadata (package-private for SvgFontLoader) --
	int ascent = 800;
	int[] bbox = { -879, -545, 1767, 934 };
	int capHeight = 662;
	int descent = -200;
	String fontFamily = "unknown";
	String fontStretch = "normal";
	int fontWeight = 400;
	final Map<Integer, Glyph> glyphs = new HashMap<>();
	boolean hasKerning = false;
	int horizAdvX = 100;
	Glyph missingGlyph = null;
	int[] panose1 = { 2, 2, 6, 3, 5, 4, 5, 2, 3, 4 };
	int underlinePosition = -150;
	int underlineThickness = 50;
	Pair<Integer, Integer> unicodeRange = new Pair<>(0x0020, 0x1F093);
	int unitsPerEm = 1000;
	int xHeight = 450;

	/** Package-private constructor — use {@link #load(Uri)} to create instances. */
	SvgFont() {}

	// ========================================================================
	// Factory
	// ========================================================================

	/**
	 * Load an SVG font from a URI.
	 * @param uri URI of the SVG font file
	 * @return the loaded font, or null on error
	 */
	public static SvgFont load(final Uri uri) {
		return SvgFontLoader.load(uri);
	}

	// ========================================================================
	// Font metrics
	// ========================================================================

	/**
	 * Get the real pixel height for all characters at the given font size.
	 * @param fontSize the requested font size
	 * @return the actual rendering height in pixels
	 */
	public int calculateFontRealHeight(final int fontSize) {
		return fontSize * this.unitsPerEm / this.capHeight;
	}

	/**
	 * Calculate the font size needed to achieve a specific pixel height.
	 * @param fontHeight the desired height in pixels
	 * @return the font size to use
	 */
	public float calculateFontSizeWithHeight(final float fontHeight) {
		return fontHeight * this.capHeight / this.unitsPerEm;
	}

	/**
	 * Get the rendering offset for proper baseline positioning.
	 * @param fontSize the font size
	 * @return the offset vector to apply
	 */
	public Vector2f calculateRenderOffset(final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		final float deltaY = realSize * this.ascent / this.unitsPerEm;
		return new Vector2f(0, deltaY);
	}

	/**
	 * Calculate the scale factor from font units to pixels.
	 * @param fontSize the font size
	 * @return the scale factor
	 */
	public float calculateScaleFactor(final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		return (float) realSize / (float) this.unitsPerEm;
	}

	/**
	 * @deprecated Use {@link #calculateScaleFactor(int)} instead.
	 */
	@Deprecated
	public float calculateSclaleFactor(final int fontSize) {
		return calculateScaleFactor(fontSize);
	}

	/**
	 * Calculate the bounding box size for a text string.
	 * @param fontSize the font size
	 * @param data the text string
	 * @return the bounding box size in pixels
	 */
	public Vector2i calculateTextSize(final int fontSize, final String data) {
		final int widthOut = calculateWidth(data, fontSize, true);
		final int realSize = calculateFontRealHeight(fontSize);
		return new Vector2i(widthOut, realSize);
	}

	/**
	 * Calculate the pixel width of a single character.
	 * @param unicodeValue the character code point
	 * @param fontSize the font size
	 * @return the width in pixels
	 */
	public int calculateWidth(final int unicodeValue, final int fontSize) {
		final Glyph glyph = getGlyph(unicodeValue);
		if (glyph == null) {
			return 0;
		}
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		return (int) (glyph.getHorizAdvX() * scale);
	}

	/**
	 * Calculate the pixel width of a text string (with kerning).
	 * @param data the text string
	 * @param fontSize the font size
	 * @return the width in pixels
	 */
	public int calculateWidth(final String data, final int fontSize) {
		return calculateWidth(data, fontSize, true);
	}

	/**
	 * Calculate the pixel width of a text string.
	 * @param data the text string
	 * @param fontSize the font size
	 * @param withKerning true to apply kerning adjustments
	 * @return the width in pixels
	 */
	public int calculateWidth(final String data, final int fontSize, final boolean withKerning) {
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		float offsetWriting = 0;
		int lastValue = 0;
		for (final char uVal : data.toCharArray()) {
			final Glyph glyph = getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				lastValue = uVal;
			}
			final float advanceX = glyph.getHorizAdvX() * scale;
			offsetWriting += advanceX;
		}
		return (int) offsetWriting;
	}

	/**
	 * Get the rendering size of a specific glyph.
	 * @param unicodeValue the character code point
	 * @param fontSize the font size
	 * @return the rendering size in pixels
	 */
	public Vector2i calculateWidthRendering(final Integer unicodeValue, final int fontSize) {
		return new Vector2i(calculateWidth(unicodeValue, fontSize), calculateFontRealHeight(fontSize));
	}

	// ========================================================================
	// Glyph access
	// ========================================================================

	/**
	 * Get a glyph by Unicode value. Returns the missing glyph if not found.
	 * @param glyphIndex the Unicode code point
	 * @return the glyph, the missing glyph fallback, or null if no missing glyph is defined
	 */
	public Glyph getGlyph(final int glyphIndex) {
		final Glyph out = this.glyphs.get(glyphIndex);
		if (out == null) {
			return this.missingGlyph;
		}
		return out;
	}

	/**
	 * Get a glyph by Unicode value. Returns null if not found.
	 * @param glyphIndex the Unicode code point
	 * @return the glyph, or null
	 */
	public Glyph getGlyphNullIfMissing(final int glyphIndex) {
		return this.glyphs.get(glyphIndex);
	}

	/**
	 * Get the number of glyphs in this font.
	 * @return the glyph count
	 */
	public int getNumGlyphs() {
		return this.glyphs.size();
	}

	// ========================================================================
	// Font properties
	// ========================================================================

	/** Maximum accented height above baseline (in font units). */
	public int getAscent() {
		return this.ascent;
	}

	/** Maximum depth below baseline (in font units, typically negative). */
	public int getDescent() {
		return this.descent;
	}

	/** Default horizontal advance width (in font units). */
	public int getHorizAdvX() {
		return this.horizAdvX;
	}

	/** Font coordinate system size (units per em). */
	public float getUnitsPerEm() {
		return this.unitsPerEm;
	}

	/** Whether this font has kerning data. */
	public boolean hasKerning() {
		return this.hasKerning;
	}

	// ========================================================================
	// Rendering (delegates to GlyphRenderer)
	// ========================================================================

	/**
	 * Render a single glyph to a grayscale raster.
	 * @param unicodeValue the Unicode code point to render
	 * @param fontSize the font size in pixels
	 * @return the rendered raster, or null if the glyph has no shape
	 */
	public GlyphRaster render(final int unicodeValue, final int fontSize) {
		return GlyphRenderer.renderGlyph(this, unicodeValue, fontSize);
	}

	/**
	 * Render a text string to a grayscale raster (with kerning).
	 * @param data the text to render
	 * @param fontSize the font size in pixels
	 * @return the rendered raster
	 */
	public GlyphRaster render(final String data, final int fontSize) {
		return GlyphRenderer.renderString(this, data, fontSize, true);
	}

	/**
	 * Render a text string to a grayscale raster.
	 * @param data the text to render
	 * @param fontSize the font size in pixels
	 * @param withKerning true to apply kerning adjustments
	 * @return the rendered raster
	 */
	public GlyphRaster render(final String data, final int fontSize, final boolean withKerning) {
		return GlyphRenderer.renderString(this, data, fontSize, withKerning);
	}
}

package org.atriasoft.esvg;

import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.awt.image.Raster;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.dataformat.xml.XmlMapper;

import org.atriasoft.esvg.font.Glyph;
import org.atriasoft.esvg.font.Kerning;
import org.atriasoft.esvg.internal.dto.FontDto;
import org.atriasoft.esvg.internal.dto.FontFaceDto;
import org.atriasoft.esvg.internal.dto.GlyphDto;
import org.atriasoft.esvg.internal.dto.HKernDto;
import org.atriasoft.esvg.internal.dto.MissingGlyphDto;
import org.atriasoft.esvg.internal.dto.SvgDto;
import org.atriasoft.esvg.render.Weight;
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
                              |                      |   |   ^ ==> getAscent(fontSize);
                              |                      |   |   |    _
                              |          /\          |   |   |    ^ ==> Font Height (height of a capital letter) = fontSize
                              |         /  \         |   |   |    |
                              |        /    \        |   |   |    |
                              |       /------\       |   |   |    |
                              |      /        \      |   |   |    |
                              |     /          \     |   |___|____|________________________==> render line
                              |                      |   |                ^
                              |                      |   |                |
                              |                      |   |                |==> getDescent(fontSize);
                              |                      |   |                |
                              *----------------------*   |                |


*/

public class EsvgFont {
	static final Logger LOGGER = LoggerFactory.getLogger(EsvgFont.class);

	private static final XmlMapper XML_MAPPER = XmlMapper.builder()
			.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false)
			.build();

	private static int parseInt(final String value, final int defaultValue) {
		if (value == null || value.isEmpty()) {
			return defaultValue;
		}
		return Integer.parseInt(value);
	}

	/**
	 * Load the file that might contain the svg
	 * @param uri File of the svg
	 * @return false : An error occured
	 * @return true : Parsing is OK
	 */
	public static EsvgFont load(final Uri uri) {
		final EsvgFont font = new EsvgFont();
		final SvgDto svg;
		try (final InputStream is = Uri.getStream(uri)) {
			if (is == null) {
				LOGGER.error("Can not read the Stream : {}", uri);
				return null;
			}
			svg = XML_MAPPER.readValue(is, SvgDto.class);
		} catch (final Exception e) {
			LOGGER.error("Failed to load SVG font from URI: {}", uri, e);
			return null;
		}
		if (svg.getDefs() == null) {
			LOGGER.error("can not load Node <defs> in svg document: {}", uri);
			return null;
		}
		final FontDto fontDto = svg.getDefs().getFont();
		if (fontDto == null) {
			LOGGER.error("can not load Node <font> in svg document: {}", uri);
			return null;
		}

		font.horizAdvX = parseInt(fontDto.getHorizAdvX(), 100);

		// Parse font-face
		final FontFaceDto face = fontDto.getFontFace();
		if (face != null) {
			font.fontFamily = face.getFontFamily() != null ? face.getFontFamily() : "unknown";
			font.fontStretch = face.getFontStretch() != null ? face.getFontStretch() : "normal";
			font.fontWeight = parseInt(face.getFontWeight(), 400);
			font.unitsPerEm = parseInt(face.getUnitsPerEm(), 1000);
			font.ascent = parseInt(face.getAscent(), 800);
			font.descent = parseInt(face.getDescent(), -200);
			font.xHeight = parseInt(face.getXHeight(), 450);
			font.capHeight = parseInt(face.getCapHeight(), 662);
			font.underlineThickness = parseInt(face.getUnderlineThickness(), 50);
			font.underlinePosition = parseInt(face.getUnderlinePosition(), -150);
			// panose-1="2 2 6 3 5 4 5 2 3 4"
			final String panoseStr = face.getPanose1();
			if (panoseStr != null) {
				final String[] tmpSplit = panoseStr.split(" ");
				font.panose1 = new int[tmpSplit.length];
				for (int iii = 0; iii < tmpSplit.length; iii++) {
					font.panose1[iii] = Integer.parseInt(tmpSplit[iii]);
				}
			}
			// bbox="-879 -545 1767 934"
			final String bboxStr = face.getBbox();
			if (bboxStr != null) {
				final String[] tmpSplit = bboxStr.split(" ");
				font.bbox = new int[tmpSplit.length];
				for (int iii = 0; iii < tmpSplit.length; iii++) {
					font.bbox[iii] = Integer.parseInt(tmpSplit[iii]);
				}
			}
			// unicode-range="U+0020-1F093"
			final String rangeStr = face.getUnicodeRange();
			if (rangeStr != null) {
				final String[] tmpSplit = rangeStr.split("-");
				final int start = Integer.parseInt(tmpSplit[0].substring(2), 16);
				final int stop = Integer.parseInt(tmpSplit[1], 16);
				font.unicodeRange = new Pair<>(start, stop);
			}
		}

		// Parse glyphs — unicode entities are already decoded by the StAX parser
		for (final GlyphDto g : fontDto.getGlyphs()) {
			final String unicode = g.getUnicode();
			if (unicode == null) {
				LOGGER.debug("Not manage glyph : '{}' (missing unicode value)", g.getGlyphName());
				continue;
			}
			if (unicode.length() != 1) {
				LOGGER.debug("not supported glyph concatenation {} value='{}'", g.getGlyphName(), unicode);
				continue;
			}
			final int unicodeValue = unicode.charAt(0);
			final int glyphHorizAdvX = parseInt(g.getHorizAdvX(), font.horizAdvX);
			final Glyph glyph = new Glyph(glyphHorizAdvX, g.getD(), g.getGlyphName(), unicode, unicodeValue);
			font.glyphs.put(unicodeValue, glyph);
		}

		// Parse missing-glyph
		final MissingGlyphDto missingDto = fontDto.getMissingGlyph();
		if (missingDto != null) {
			final int mgHorizAdvX = parseInt(missingDto.getHorizAdvX(), font.horizAdvX);
			final String mgUnicode = missingDto.getUnicode();
			final int mgUnicodeValue = mgUnicode != null && mgUnicode.length() == 1 ? mgUnicode.charAt(0) : 0;
			font.missingGlyph = new Glyph(mgHorizAdvX, missingDto.getD(), missingDto.getGlyphName(),
					mgUnicode, mgUnicodeValue);
		}

		// Parse hkern
		for (final HKernDto hk : fontDto.getHkerns()) {
			final String g1 = hk.getG1();
			final String g2 = hk.getG2();
			if (g1 == null || g2 == null) {
				continue;
			}
			final float offset = hk.getK() != null ? Float.parseFloat(hk.getK()) : 0.0f;
			if (offset == 0.0f) {
				continue;
			}
			final String[] g1Split = g1.split(",");
			final String[] g2Split = g2.split(",");
			// create the list of kerning of the next elements
			final List<Kerning> elementsKerning = new ArrayList<>();
			for (final String element : g2Split) {
				for (final Map.Entry<Integer, Glyph> entry : font.glyphs.entrySet()) {
					if (entry.getValue().getName() != null && entry.getValue().getName().equals(element)) {
						elementsKerning.add(new Kerning(offset, entry.getKey()));
						break;
					}
				}
			}
			for (final String element : g1Split) {
				for (final Map.Entry<Integer, Glyph> entry : font.glyphs.entrySet()) {
					if (entry.getValue().getName() != null && entry.getValue().getName().equals(element)) {
						entry.getValue().addKerning(elementsKerning);
						font.hasKerning = true;
						break;
					}
				}
			}
		}
		return font;
	}

	// The maximum accented height of the font within the font coordinate system.
	private int ascent = 800; // this is the height of the font (on top...)
	private int[] bbox = { -879, -545, 1767, 934 };
	// The height of uppercase glyphs in the font within the font coordinate system.
	private int capHeight = 662;
	// The maximum unaccented depth of the font within the font coordinate system.
	private int descent = -200; // lower size of the font
	private String fontFamily = "unknown";
	private String fontStretch = "normal";
	private int fontWeight = 400;
	private final Map<Integer, Glyph> glyphs = new HashMap<>();
	private boolean hasKerning = false;
	// The horizontal advance after rendering the glyph in horizontal orientation. If the attribute is not specified, the effect is as if the attribute were set to the value of the font's 'horiz-adv-x' attribute.
	// Glyph widths are required to be non-negative, even if the glyph is typically rendered right-to-left, as in Hebrew and Arabic scripts.
	private int horizAdvX = 100;
	private Glyph missingGlyph = null;
	private int[] panose1 = { 2, 2, 6, 3, 5, 4, 5, 2, 3, 4 };
	private int underlinePosition = -150;
	private int underlineThickness = 50;
	private Pair<Integer, Integer> unicodeRange = new Pair<>(0x0020, 0x1F093);
	private int unitsPerEm = 1000; // full size of the font
	// The height of lowercase glyphs in the font within the font coordinate system.
	private int xHeight = 450;

	/**
	 * Get the font real size use (height) for all the characters.
	 * @param fontSize size of the font the user require
	 * @return Real size in pixel of element can impact the output
	 */
	public int calculateFontRealHeight(final int fontSize) {
		return fontSize * this.unitsPerEm / this.capHeight;

	}

	public float calculateFontSizeWithHeight(final float fontHeight) {
		return fontHeight * this.capHeight / this.unitsPerEm;
	}

	public Vector2f calculateRenderOffset(final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		final float deltaY = realSize * this.ascent / this.unitsPerEm;
		return new Vector2f(0, deltaY);
	}

	public float calculateSclaleFactor(final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		return (float) realSize / (float) this.unitsPerEm;
	}

	public Vector2i calculateTextSize(final int fontSize, final String data) {
		final boolean withKerning = true;
		final int widthOut = calculateWidth(data, fontSize, withKerning);

		final int realSize = calculateFontRealHeight(fontSize);
		return new Vector2i(widthOut, realSize);
		/*
		float scale = (float) realSize / (float) this.unitsPerEm;

		int offsetWriting = 0;
		int lastValue = 0;
		for (char uVal : data.toCharArray()) {
			Glyph glyph = getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				lastValue = uVal;
			}

			float advenceXLocal = glyph.getHorizAdvX() * scale;
			// No generation of output ...
			offsetWriting += advenceXLocal;
		}
		return new Vector2i(offsetWriting, realSize);
		*/
	}

	public int calculateWidth(final int uVal, final int fontSize) {
		final Glyph glyph = getGlyph(uVal);
		if (glyph == null) {
			return 0;
		}
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		return (int) (glyph.getHorizAdvX() * scale);
	}

	public int calculateWidth(final String uVal, final int fontSize) {
		return calculateWidth(uVal, fontSize, true);
	}

	public int calculateWidth(final String data, final int fontSize, final boolean withKerning) {
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		//LOGGER.error("scale =" + scale+ " font size = " + fontSize + "  realSize=" + realSize);
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

			final float advenceXLocal = glyph.getHorizAdvX() * scale;
			offsetWriting += advenceXLocal;
			//LOGGER.error("offset X =" + offsetWriting + " + " + advenceXLocal + "    " + uVal);
		}
		return (int) offsetWriting;
	}

	/**
	 * Get the rendering size of the specific glyph (size rendered in the Weight class).
	 * @param unicodeValue Unicode value to render
	 * @param fontSize Size of the font
	 * @return the size in pixel of the rendering elements
	 */
	public Vector2i calculateWidthRendering(final Integer unicodeValue, final int fontSize) {
		return new Vector2i(calculateWidth(unicodeValue, fontSize), calculateFontRealHeight(fontSize));
	}

	public int getDescent() {
		return this.descent;
	}

	public Glyph getGlyph(final int glyphIndex) {
		final Glyph out = this.glyphs.get(glyphIndex);
		if (out == null) {
			return this.missingGlyph;
		}
		return out;
	}

	public Glyph getGlyphNullIfMissing(final int glyphIndex) {
		final Glyph out = this.glyphs.get(glyphIndex);
		if (out == null) {
			return null;
		}
		return out;
	}

	public int getHorizAdvX() {
		return this.horizAdvX;
	}

	/**
	 * Get the number of available glyph in the Font
	 * @return the glyph count.
	 */
	public int getNumGlyphs() {
		return this.glyphs.size();
	}

	public float getUnitsPerEm() {
		return this.unitsPerEm;
	}

	/**
	 * Check if the font have some kerning data
	 * @return true if kerning is availlable.
	 */
	public boolean hasKerning() {
		return this.hasKerning;
	}

	public Weight render(final int uVal, final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		final Glyph glyph = getGlyph(uVal);
		if (glyph == null) {
			return null;
		}
		final Shape shape = glyph.getShape();
		if (shape == null) {
			return null;
		}
		final float scale = (float) realSize / (float) this.unitsPerEm;
		final Vector2i renderSize = calculateWidthRendering(uVal, fontSize);
		final int w = Math.max(1, renderSize.x());
		final int h = Math.max(1, renderSize.y());

		final BufferedImage image = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_GRAY);
		final Graphics2D g2d = image.createGraphics();
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.setColor(java.awt.Color.WHITE);
		final AffineTransform tx = new AffineTransform();
		tx.scale(scale, scale);
		tx.translate(0, -this.descent);
		g2d.setTransform(tx);
		g2d.fill(shape);
		g2d.dispose();

		final Weight weight = new Weight(new Vector2i(w, h));
		final Raster raster = image.getRaster();
		for (int yyy = 0; yyy < h; yyy++) {
			for (int xxx = 0; xxx < w; xxx++) {
				weight.set(new Vector2i(xxx, yyy), raster.getSample(xxx, yyy, 0) / 255.0f);
			}
		}
		return weight;
	}

	public Weight render(final String uVal, final int fontSize) {
		return render(uVal, fontSize, true);
	}

	public Weight render(final String data, final int fontSize, final boolean withKerning) {
		final int widthOut = calculateWidth(data, fontSize, withKerning);

		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;

		final Weight weight = new Weight(new Vector2i(Math.max(1, widthOut), realSize));

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
				LOGGER.debug("    ==> kerning offset = {}", (glyph.getKerning(lastValue) * scale));
				lastValue = uVal;
			}

			final float advenceXLocal = glyph.getHorizAdvX() * scale;

			final Shape shape = glyph.getShape();
			if (shape != null) {
				final Weight rendered = render(uVal, fontSize);
				if (rendered != null) {
					weight.fusion(rendered, (int) offsetWriting, 0);
				}
			}
			offsetWriting += advenceXLocal;
		}
		return weight;
	}
}

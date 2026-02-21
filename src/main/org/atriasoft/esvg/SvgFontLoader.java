package org.atriasoft.esvg;

import java.io.InputStream;
import java.util.ArrayList;
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
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.util.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Loads SVG font files using Jackson XmlMapper and populates {@link SvgFont} instances.
 * Package-private: external code should use {@link SvgFont#load(Uri)}.
 */
final class SvgFontLoader {
	private static final Logger LOGGER = LoggerFactory.getLogger(SvgFontLoader.class);

	private static final XmlMapper XML_MAPPER = XmlMapper.builder()
			.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false)
			.build();

	static int parseInt(final String value, final int defaultValue) {
		if (value == null || value.isEmpty()) {
			return defaultValue;
		}
		return Integer.parseInt(value);
	}

	/**
	 * Load an SVG font file and return a fully populated {@link SvgFont}.
	 * @param uri URI of the SVG font file
	 * @return the loaded font, or null on error
	 */
	static SvgFont load(final Uri uri) {
		final SvgFont font = new SvgFont();
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

	private SvgFontLoader() {}
}

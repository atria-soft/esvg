package org.atriasoft.esvg;

import java.io.IOException;
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
		try {
			return Integer.parseInt(value);
		} catch (final NumberFormatException e) {
			LOGGER.warn("Invalid integer value '{}', using default {}", value, defaultValue);
			return defaultValue;
		}
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
		} catch (final IOException e) {
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

		try {
			return parseFont(font, fontDto);
		} catch (final NumberFormatException e) {
			LOGGER.error("Malformed numeric attribute in SVG font: {}", uri, e);
			return null;
		}
	}

	private static SvgFont parseFont(final SvgFont font, final FontDto fontDto) {
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
				final String[] panoseParts = panoseStr.split(" ");
				font.panose1 = new int[panoseParts.length];
				for (int i = 0; i < panoseParts.length; i++) {
					font.panose1[i] = Integer.parseInt(panoseParts[i]);
				}
			}
			// bbox="-879 -545 1767 934"
			final String bboxStr = face.getBbox();
			if (bboxStr != null) {
				final String[] bboxParts = bboxStr.split(" ");
				font.bbox = new int[bboxParts.length];
				for (int i = 0; i < bboxParts.length; i++) {
					font.bbox[i] = Integer.parseInt(bboxParts[i]);
				}
			}
			// unicode-range="U+0020-1F093"
			final String rangeStr = face.getUnicodeRange();
			if (rangeStr != null && rangeStr.contains("-")) {
				final String[] rangeParts = rangeStr.split("-", 2);
				if (rangeParts.length == 2) {
					final int start = Integer.parseInt(rangeParts[0].substring(2), 16);
					final int stop = Integer.parseInt(rangeParts[1], 16);
					font.unicodeRange = new Pair<>(start, stop);
				}
			}
		}

		// Parse glyphs — unicode entities are already decoded by the StAX parser
		// Glyphs without a single unicode value (alternates, ligatures) are expected in a font: traced only.
		int skippedGlyphs = 0;
		for (final GlyphDto glyphDto : fontDto.getGlyphs()) {
			final String unicode = glyphDto.getUnicode();
			if (unicode == null) {
				LOGGER.trace("Not manage glyph : '{}' (missing unicode value)", glyphDto.getGlyphName());
				skippedGlyphs++;
				continue;
			}
			if (unicode.length() != 1) {
				LOGGER.trace("not supported glyph concatenation {} value='{}'", glyphDto.getGlyphName(), unicode);
				skippedGlyphs++;
				continue;
			}
			final int unicodeValue = unicode.charAt(0);
			final int glyphHorizAdvX = parseInt(glyphDto.getHorizAdvX(), font.horizAdvX);
			final Glyph glyph = new Glyph(glyphHorizAdvX, glyphDto.getD(), glyphDto.getGlyphName(), unicode, unicodeValue);
			font.glyphs.put(unicodeValue, glyph);
		}
		if (skippedGlyphs > 0) {
			LOGGER.debug("Font '{}': {} glyph(s) without a single unicode value skipped", font.fontFamily, skippedGlyphs);
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
		for (final HKernDto hkernDto : fontDto.getHkerns()) {
			final String g1 = hkernDto.getG1();
			final String g2 = hkernDto.getG2();
			if (g1 == null || g2 == null) {
				continue;
			}
			final float offset = hkernDto.getK() != null ? Float.parseFloat(hkernDto.getK()) : 0.0f;
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

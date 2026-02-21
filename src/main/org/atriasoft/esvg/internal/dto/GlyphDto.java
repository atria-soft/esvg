package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for a {@code <glyph>} element in an SVG font file.
 * <p>
 * Each glyph maps a Unicode character to an SVG path outline and an optional
 * horizontal advance width override.
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class GlyphDto {
	@JacksonXmlProperty(isAttribute = true, localName = "glyph-name")
	private String glyphName;

	@JacksonXmlProperty(isAttribute = true)
	private String unicode;

	@JacksonXmlProperty(isAttribute = true)
	private String d;

	@JacksonXmlProperty(isAttribute = true, localName = "horiz-adv-x")
	private String horizAdvX;

	/** Glyph name identifier (e.g. "A", "space", "ampersand"). */
	public String getGlyphName() {
		return this.glyphName;
	}

	/** Unicode character this glyph represents. */
	public String getUnicode() {
		return this.unicode;
	}

	/** SVG path data string for the glyph outline. */
	public String getD() {
		return this.d;
	}

	/** Per-glyph horizontal advance width override (null = use font default). */
	public String getHorizAdvX() {
		return this.horizAdvX;
	}
}

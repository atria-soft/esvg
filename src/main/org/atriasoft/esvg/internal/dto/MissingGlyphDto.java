package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for the {@code <missing-glyph>} element in an SVG font file.
 * <p>
 * Defines the fallback glyph rendered when a requested character is not found in the font.
 * Has the same structure as a regular {@link GlyphDto}.
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class MissingGlyphDto {
	@JacksonXmlProperty(isAttribute = true, localName = "horiz-adv-x")
	private String horizAdvX;

	@JacksonXmlProperty(isAttribute = true)
	private String d;

	@JacksonXmlProperty(isAttribute = true, localName = "glyph-name")
	private String glyphName;

	@JacksonXmlProperty(isAttribute = true)
	private String unicode;

	/** Horizontal advance width for the missing glyph. */
	public String getHorizAdvX() {
		return this.horizAdvX;
	}

	/** SVG path data string for the missing glyph outline. */
	public String getD() {
		return this.d;
	}

	/** Name of the missing glyph. */
	public String getGlyphName() {
		return this.glyphName;
	}

	/** Unicode value (usually not set for missing-glyph). */
	public String getUnicode() {
		return this.unicode;
	}
}

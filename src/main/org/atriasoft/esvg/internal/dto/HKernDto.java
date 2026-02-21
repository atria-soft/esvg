package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for an {@code <hkern>} (horizontal kerning) element in an SVG font file.
 * <p>
 * Defines kerning adjustments between pairs of glyphs identified by name.
 * {@code g1} and {@code g2} are comma-separated lists of glyph names,
 * and {@code k} is the kerning offset in font units.
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class HKernDto {
	@JacksonXmlProperty(isAttribute = true)
	private String g1;

	@JacksonXmlProperty(isAttribute = true)
	private String g2;

	@JacksonXmlProperty(isAttribute = true)
	private String k;

	/** First glyph name(s) in the kerning pair (comma-separated). */
	public String getG1() {
		return this.g1;
	}

	/** Second glyph name(s) in the kerning pair (comma-separated). */
	public String getG2() {
		return this.g2;
	}

	/** Kerning offset in font units. */
	public String getK() {
		return this.k;
	}
}

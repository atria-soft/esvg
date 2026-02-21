package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

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

	public String getGlyphName() {
		return this.glyphName;
	}

	public String getUnicode() {
		return this.unicode;
	}

	public String getD() {
		return this.d;
	}

	public String getHorizAdvX() {
		return this.horizAdvX;
	}
}

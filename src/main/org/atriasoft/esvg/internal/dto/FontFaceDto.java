package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

@JsonIgnoreProperties(ignoreUnknown = true)
public class FontFaceDto {
	@JacksonXmlProperty(isAttribute = true, localName = "font-family")
	private String fontFamily;

	@JacksonXmlProperty(isAttribute = true, localName = "font-weight")
	private String fontWeight;

	@JacksonXmlProperty(isAttribute = true, localName = "font-stretch")
	private String fontStretch;

	@JacksonXmlProperty(isAttribute = true, localName = "units-per-em")
	private String unitsPerEm;

	@JacksonXmlProperty(isAttribute = true)
	private String ascent;

	@JacksonXmlProperty(isAttribute = true)
	private String descent;

	@JacksonXmlProperty(isAttribute = true, localName = "x-height")
	private String xHeight;

	@JacksonXmlProperty(isAttribute = true, localName = "cap-height")
	private String capHeight;

	@JacksonXmlProperty(isAttribute = true, localName = "underline-thickness")
	private String underlineThickness;

	@JacksonXmlProperty(isAttribute = true, localName = "underline-position")
	private String underlinePosition;

	@JacksonXmlProperty(isAttribute = true, localName = "panose-1")
	private String panose1;

	@JacksonXmlProperty(isAttribute = true)
	private String bbox;

	@JacksonXmlProperty(isAttribute = true, localName = "unicode-range")
	private String unicodeRange;

	public String getFontFamily() {
		return this.fontFamily;
	}

	public String getFontWeight() {
		return this.fontWeight;
	}

	public String getFontStretch() {
		return this.fontStretch;
	}

	public String getUnitsPerEm() {
		return this.unitsPerEm;
	}

	public String getAscent() {
		return this.ascent;
	}

	public String getDescent() {
		return this.descent;
	}

	public String getXHeight() {
		return this.xHeight;
	}

	public String getCapHeight() {
		return this.capHeight;
	}

	public String getUnderlineThickness() {
		return this.underlineThickness;
	}

	public String getUnderlinePosition() {
		return this.underlinePosition;
	}

	public String getPanose1() {
		return this.panose1;
	}

	public String getBbox() {
		return this.bbox;
	}

	public String getUnicodeRange() {
		return this.unicodeRange;
	}
}

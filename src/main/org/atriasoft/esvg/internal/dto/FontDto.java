package org.atriasoft.esvg.internal.dto;

import java.util.ArrayList;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonMerge;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlElementWrapper;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

@JsonIgnoreProperties(ignoreUnknown = true)
public class FontDto {
	@JacksonXmlProperty(isAttribute = true, localName = "id")
	private String id;

	@JacksonXmlProperty(isAttribute = true, localName = "horiz-adv-x")
	private String horizAdvX;

	@JacksonXmlProperty(localName = "font-face")
	private FontFaceDto fontFace;

	@JacksonXmlProperty(localName = "missing-glyph")
	private MissingGlyphDto missingGlyph;

	@JacksonXmlElementWrapper(useWrapping = false)
	@JacksonXmlProperty(localName = "glyph")
	@JsonMerge
	private List<GlyphDto> glyphs = new ArrayList<>();

	@JacksonXmlElementWrapper(useWrapping = false)
	@JacksonXmlProperty(localName = "hkern")
	@JsonMerge
	private List<HKernDto> hkerns = new ArrayList<>();

	public String getHorizAdvX() {
		return this.horizAdvX;
	}

	public FontFaceDto getFontFace() {
		return this.fontFace;
	}

	public MissingGlyphDto getMissingGlyph() {
		return this.missingGlyph;
	}

	public List<GlyphDto> getGlyphs() {
		return this.glyphs;
	}

	public List<HKernDto> getHkerns() {
		return this.hkerns;
	}
}

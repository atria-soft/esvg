package org.atriasoft.esvg.internal.dto;

import java.util.ArrayList;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonMerge;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlElementWrapper;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for the {@code <font>} element in an SVG font file.
 * <p>
 * Contains the font-level metadata ({@code horiz-adv-x}), the {@code <font-face>} descriptor,
 * the {@code <missing-glyph>}, and lists of {@code <glyph>} and {@code <hkern>} elements.
 * <p>
 * Note: {@code @JsonMerge} with {@code useWrapping = false} is required because
 * {@code <glyph>} and {@code <hkern>} elements are interlaced siblings (not wrapped in a container).
 */
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

	/** Get the default horizontal advance width. */
	public String getHorizAdvX() {
		return this.horizAdvX;
	}

	/** Get the {@code <font-face>} descriptor. */
	public FontFaceDto getFontFace() {
		return this.fontFace;
	}

	/** Get the {@code <missing-glyph>} fallback glyph. */
	public MissingGlyphDto getMissingGlyph() {
		return this.missingGlyph;
	}

	/** Get all {@code <glyph>} elements. */
	public List<GlyphDto> getGlyphs() {
		return this.glyphs;
	}

	/** Get all {@code <hkern>} (horizontal kerning) elements. */
	public List<HKernDto> getHkerns() {
		return this.hkerns;
	}
}

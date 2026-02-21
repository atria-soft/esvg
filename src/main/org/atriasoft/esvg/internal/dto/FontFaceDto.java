package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for the {@code <font-face>} element in an SVG font file.
 * <p>
 * Contains font metadata: family name, weight, stretch, metrics (ascent, descent,
 * cap-height, x-height, units-per-em), and classification data (panose-1, bbox, unicode-range).
 *
 * @see <a href="https://www.w3.org/TR/SVGTiny12/fonts.html">SVG Tiny 1.2 Fonts</a>
 */
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

	/** Font family name (e.g. "FreeSans"). */
	public String getFontFamily() {
		return this.fontFamily;
	}

	/** Font weight (e.g. "400" for normal, "700" for bold). */
	public String getFontWeight() {
		return this.fontWeight;
	}

	/** Font stretch (e.g. "normal", "condensed"). */
	public String getFontStretch() {
		return this.fontStretch;
	}

	/** Units per em square (typically "1000"). */
	public String getUnitsPerEm() {
		return this.unitsPerEm;
	}

	/** Maximum height above baseline in font units. */
	public String getAscent() {
		return this.ascent;
	}

	/** Maximum depth below baseline in font units (typically negative). */
	public String getDescent() {
		return this.descent;
	}

	/** Height of lowercase letters in font units. */
	public String getXHeight() {
		return this.xHeight;
	}

	/** Height of capital letters in font units. */
	public String getCapHeight() {
		return this.capHeight;
	}

	/** Thickness of underline in font units. */
	public String getUnderlineThickness() {
		return this.underlineThickness;
	}

	/** Vertical position of underline relative to baseline. */
	public String getUnderlinePosition() {
		return this.underlinePosition;
	}

	/** PANOSE-1 classification (space-separated integers, e.g. "2 2 6 3 5 4 5 2 3 4"). */
	public String getPanose1() {
		return this.panose1;
	}

	/** Bounding box (space-separated: "xMin yMin xMax yMax"). */
	public String getBbox() {
		return this.bbox;
	}

	/** Unicode range (e.g. "U+0020-1F093"). */
	public String getUnicodeRange() {
		return this.unicodeRange;
	}
}

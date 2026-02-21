package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for the {@code <defs>} element inside an SVG font file.
 * Contains a single {@code <font>} child element.
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class DefsDto {
	@JacksonXmlProperty(localName = "font")
	private FontDto font;

	/** Get the {@code <font>} element. */
	public FontDto getFont() {
		return this.font;
	}
}

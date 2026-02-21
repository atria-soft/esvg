package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

/**
 * DTO for the root {@code <svg>} element of an SVG font file.
 * Maps the top-level SVG structure containing a {@code <defs>} child.
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class SvgDto {
	@JacksonXmlProperty(localName = "defs")
	private DefsDto defs;

	/** Get the {@code <defs>} section. */
	public DefsDto getDefs() {
		return this.defs;
	}
}

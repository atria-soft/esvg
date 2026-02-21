package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

@JsonIgnoreProperties(ignoreUnknown = true)
public class DefsDto {
	@JacksonXmlProperty(localName = "font")
	private FontDto font;

	public FontDto getFont() {
		return this.font;
	}
}

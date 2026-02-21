package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

@JsonIgnoreProperties(ignoreUnknown = true)
public class SvgDto {
	@JacksonXmlProperty(localName = "defs")
	private DefsDto defs;

	public DefsDto getDefs() {
		return this.defs;
	}
}

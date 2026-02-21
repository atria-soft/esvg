package org.atriasoft.esvg.internal.dto;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty;

@JsonIgnoreProperties(ignoreUnknown = true)
public class HKernDto {
	@JacksonXmlProperty(isAttribute = true)
	private String g1;

	@JacksonXmlProperty(isAttribute = true)
	private String g2;

	@JacksonXmlProperty(isAttribute = true)
	private String k;

	public String getG1() {
		return this.g1;
	}

	public String getG2() {
		return this.g2;
	}

	public String getK() {
		return this.k;
	}
}

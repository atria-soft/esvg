package org.atriasoft.esvg.render;

public record RenderingConfig(
		int recurtionMax,
		float interpolationThreshold,
		int numberOfScanline) {}

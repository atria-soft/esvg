package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestColor {
	@Test
	public void testTestColorBlending() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestColorblending.svg"), data);
		doc.generateAnImage(new Uri("TestColorblending.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestColorBlendingandopacity() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' opacity='0.7' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestColorblendingandopacity.svg"), data);
		doc.generateAnImage(new Uri("TestColorblendingandopacity.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestColorMultiplelayer() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='50'   y='5' width='15' height='75' stroke='blue' stroke-width='9' fill='green'/>"
				+ "	<rect x='12.5' y='12.5' width='75' height='30' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' opacity='0.7' />"
				+ "	<rect x='30'   y='30' width='20' height='20' stroke='orange' stroke-width='1' fill='violet'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestColormultiplelayer.svg"), data);
		doc.generateAnImage(new Uri("TestColormultiplelayer.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestColorOpacity() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-width='3' fill='#F00' opacity='0.5' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestColoropacity.svg"), data);
		doc.generateAnImage(new Uri("TestColoropacity.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
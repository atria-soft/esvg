package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestCircle {
	
	@Test
	public void testTestCircleFill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<circle cx='50' cy='50' r='40' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCirclefill.svg"), data);
		doc.generateAnImage(new Uri("TestCirclefill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCircleFillandstroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' fill='red' />"
				+ "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCirclefillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestCirclefillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCircleStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCirclestroke.svg"), data);
		doc.generateAnImage(new Uri("TestCirclestroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
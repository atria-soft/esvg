package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestPolyline {
	@Test
	public void testTestPolyLineFill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<polyline points='20,20 40,25 60,40 80,90 90,50 5,90' fill='orange' />"
				+ "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPolyLinefill.svg"), data);
		doc.generateAnImage(new Uri("TestPolyLinefill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPolyLineFillAndStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 40,25 60,40 80,90 90,50 5,90' stroke='green' stroke-width='3' fill='orange' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPolyLinefillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestPolyLinefillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPolyLineStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 40,25 60,40 80,90 90,50 5,90' stroke='green' stroke-width='3' fill='none' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPolyLinestroke.svg"), data);
		doc.generateAnImage(new Uri("TestPolyLinestroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
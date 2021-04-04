package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestPolygon {
	@Test
	public void testTestPolygonFill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<polygon points='50,10 90,50 10,80' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPolygonfill.svg"), data);
		doc.generateAnImage(new Uri("TestPolygonfill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPolygonFillAndStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polygon points='50,10 90,50 10,80' stroke='green' stroke-width='3' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPolygonfillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestPolygonfillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPolygonStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<polygon points='50,10 90,50 10,80' stroke='green' stroke-width='3' />"
				+ "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPolygonstroke.svg"), data);
		doc.generateAnImage(new Uri("TestPolygonstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestEllipse {
	
	@Test
	public void testTestEllipseFill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<ellipse cx='50' cy='50' rx='80' ry='30' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestEllipsefill.svg"), data);
		doc.generateAnImage(new Uri("TestEllipsefill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestEllipseFillAndStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<ellipse cx='50' cy='50' rx='80' ry='30' stroke='green' stroke-width='3' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestEllipsefillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestEllipsefillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestEllipseStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<ellipse cx='50' cy='50' rx='80' ry='30' stroke='green' stroke-width='3' />"
				+ "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestEllipsestroke.svg"), data);
		doc.generateAnImage(new Uri("TestEllipsestroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
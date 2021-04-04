package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestRectangle {
	@Test
	public void testTestRectangleCornedfill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' fill='red' />"
				+ "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestRectanglecornedfill.svg"), data);
		doc.generateAnImage(new Uri("TestRectanglecornedfill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestRectangleCornedfillandstroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestRectanglecornedfillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestRectanglecornedfillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestRectangleCornedstroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestRectanglecornedstroke.svg"), data);
		doc.generateAnImage(new Uri("TestRectanglecornedstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestRectangleFill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<rect x='12.5' y='12.5' width='75' height='50' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestRectanglefill.svg"), data);
		doc.generateAnImage(new Uri("TestRectanglefill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestRectangleFillandstroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestRectanglefillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestRectanglefillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestRectangleStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestRectanglestroke.svg"), data);
		doc.generateAnImage(new Uri("TestRectanglestroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
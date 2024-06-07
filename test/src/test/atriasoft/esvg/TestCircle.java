package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestCircle {
	
	@Test
	public void testTestCircleFill() throws RuntimeException {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='100' width='100'>\
					<circle cx='50' cy='50' r='40' fill='red' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCirclefill.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCirclefill.png"));
	}
	
	@Test
	public void testTestCircleFillandstroke() throws RuntimeException {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='100' width='100'>\
					<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' fill='red' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCirclefillandstroke.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCirclefillandstroke.png"));
	}
	
	@Test
	public void testTestCircleStroke() throws RuntimeException {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='100' width='100'>\
					<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCirclestroke.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCirclestroke.png"));
	}
}
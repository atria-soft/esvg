package test.atriasoft.esvg;

import org.atriasoft.esvg.Esvg;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestText {
	@Test
	public void testTextBase() {
		Esvg.init();
		//@formatter:off
		String data = "\n"
				+ "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
				+ "<svg\n"
				+ "   width='300'\n"
				+ "   height='300'\n"
				+ "   version='1.1'>\n"
				+ "  <g>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-weight:normal;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='10'\n"
				+ "       y='50'>Hello</text>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-weight:bold;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='30'\n"
				+ "       y='100'>Hello Bold</text>\n"
				+ "    <text\n"
				+ "       style='font-style:italic;font-weight:normal;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='50'\n"
				+ "       y='150'>Hello Italic</text>\n"
				+ "    <text\n"
				+ "       style='font-style:italic;font-weight:bold;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='70'\n"
				+ "       y='200'>Hello Bold Italic</text>\n"
				+ "    <text\n"
				+ "       style='font-style:italic;font-weight:bold;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='-274.79779'\n"
				+ "       y='72.401932'\n"
				+ "       transform='rotate(-137.0948)'>Hello Rotated</text>\n"
				+ "  </g>\n"
				+ "</svg>\n";
		//@formatter:on
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(()-> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestTextFull.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestTextFull.png"));
	}
	
	public void testTextFull() {
		//@formatter:off
		String data = "\n"
				+ "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
				+ "<svg\n"
				+ "   width='300'\n"
				+ "   height='300'\n"
				+ "   version='1.1'>\n"
				+ "  <g>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:6.35px;line-height:1.25;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583'\n"
				+ "       x='52.662182'\n"
				+ "       y='11.725324'><tspan\n"
				+ "         sodipodi:role='line'\n"
				+ "         x='52.662182'\n"
				+ "         y='11.725324'\n"
				+ "         style='font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:6.35px;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;stroke-width:0.264583'>H<tspan\n"
				+ "   style='fill:#d38b00;fill-opacity:1'\n"
				+ "   >e</tspan>llo</tspan><tspan\n"
				+ "         sodipodi:role='line'\n"
				+ "         x='52.662182'\n"
				+ "         y='19.662823'\n"
				+ "         style='font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:6.35px;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;stroke-width:0.264583'\n"
				+ "         >sq<tspan\n"
				+ "   style='fill:#8c0000;fill-opacity:1'>m</tspan>l</tspan><tspan\n"
				+ "         x='52.662182'\n"
				+ "         y='27.600323'\n"
				+ "         style='font-style:italic;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:6.35px;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;stroke-width:0.264583'\n"
				+ "         >k<tspan\n"
				+ "   style='fill:#000063;fill-opacity:1'\n"
				+ "   >s</tspan>d</tspan></text>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='1.3595439'\n"
				+ "       y='44.163139'><tspan\n"
				+ "         x='1.3595439'\n"
				+ "         y='44.163139'\n"
				+ "         style='stroke-width:0.264583;font-family:sans-serif;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'>Hello</tspan></text>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='1.1807559'\n"
				+ "       y='55.513321'><tspan\n"
				+ "         x='1.1807559'\n"
				+ "         y='55.513321'\n"
				+ "         style='stroke-width:0.264583;font-weight:bold;font-family:sans-serif;font-style:normal;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal'>Hello Bold</tspan></text>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='1.196579'\n"
				+ "       y='65.77121'><tspan\n"
				+ "         x='1.196579'\n"
				+ "         y='65.77121'\n"
				+ "         style='stroke-width:0.264583;font-style:italic;font-family:sans-serif;font-weight:normal;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal'>Hello Italic</tspan></text>\n"
				+ "    <text\n"
				+ "       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'\n"
				+ "       x='1.9766912'\n"
				+ "       y='76.594482'><tspan\n"
				+ "         x='1.9766912'\n"
				+ "         y='76.594482'\n"
				+ "         style='stroke-width:0.264583;font-weight:bold;font-style:italic;font-family:sans-serif;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal'>Hello Bold Italic</tspan></text>\n"
				+ "  </g>\n"
				+ "</svg>\n";
		//@formatter:on
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(()-> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestTextFull.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestTextFull.png"));
	}
}

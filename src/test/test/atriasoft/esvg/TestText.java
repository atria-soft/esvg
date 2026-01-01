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
		final String data = """
			<?xml version='1.0' encoding='UTF-8' standalone='no'?>
			<svg
			   width='300'
			   height='300'
			   version='1.1'>
			  <g>
			    <text
			       style='font-style:normal;font-weight:normal;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='10'
			       y='50'>Hello</text>
			    <text
			       style='font-style:normal;font-weight:bold;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='30'
			       y='100'>Hello Bold</text>
			    <text
			       style='font-style:italic;font-weight:normal;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='50'
			       y='150'>Hello Italic</text>
			    <text
			       style='font-style:italic;font-weight:bold;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='70'
			       y='200'>Hello Bold Italic</text>
			    <text
			       style='font-style:italic;font-weight:bold;font-size:15.5px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='-274.79779'
			       y='72.401932'
			       transform='rotate(-137.0948)'>Hello Rotated</text>
			  </g>
			</svg>
			""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestTextFull.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestTextFull.png"));
	}
	
	public void testTextFull() {
		//@formatter:off
		final String data = """
			<?xml version='1.0' encoding='UTF-8' standalone='no'?>
			<svg
			   width='300'
			   height='300'
			   version='1.1'>
			  <g>
			    <text
			       style='font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:6.35px;line-height:1.25;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583'
			       x='52.662182'
			       y='11.725324'><tspan
			         sodipodi:role='line'
			         x='52.662182'
			         y='11.725324'
			         style='font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:6.35px;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;stroke-width:0.264583'>H<tspan
			   style='fill:#d38b00;fill-opacity:1'
			   >e</tspan>llo</tspan><tspan
			         sodipodi:role='line'
			         x='52.662182'
			         y='19.662823'
			         style='font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:6.35px;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;stroke-width:0.264583'
			         >sq<tspan
			   style='fill:#8c0000;fill-opacity:1'>m</tspan>l</tspan><tspan
			         x='52.662182'
			         y='27.600323'
			         style='font-style:italic;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:6.35px;font-family:sans-serif;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;stroke-width:0.264583'
			         >k<tspan
			   style='fill:#000063;fill-opacity:1'
			   >s</tspan>d</tspan></text>
			    <text
			       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='1.3595439'
			       y='44.163139'><tspan
			         x='1.3595439'
			         y='44.163139'
			         style='stroke-width:0.264583;font-family:sans-serif;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'>Hello</tspan></text>
			    <text
			       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='1.1807559'
			       y='55.513321'><tspan
			         x='1.1807559'
			         y='55.513321'
			         style='stroke-width:0.264583;font-weight:bold;font-family:sans-serif;font-style:normal;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal'>Hello Bold</tspan></text>
			    <text
			       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='1.196579'
			       y='65.77121'><tspan
			         x='1.196579'
			         y='65.77121'
			         style='stroke-width:0.264583;font-style:italic;font-family:sans-serif;font-weight:normal;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal'>Hello Italic</tspan></text>
			    <text
			       style='font-style:normal;font-weight:normal;font-size:5.64444444px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.264583;font-stretch:normal;font-variant:normal;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal;'
			       x='1.9766912'
			       y='76.594482'><tspan
			         x='1.9766912'
			         y='76.594482'
			         style='stroke-width:0.264583;font-weight:bold;font-style:italic;font-family:sans-serif;font-stretch:normal;font-variant:normal;font-size:5.64444444px;font-variant-ligatures:normal;font-variant-caps:normal;font-variant-numeric:normal;font-variant-east-asian:normal'>Hello Bold Italic</tspan></text>
			  </g>
			</svg>
			""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestTextFull.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestTextFull.png"));
	}
}

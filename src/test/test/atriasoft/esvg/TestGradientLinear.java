package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestGradientLinear {
	@Test
	public void testTestGradientLinearDiag1() {
		//@formatter:off
		final String data = """
			<?xml version='1.0' encoding='UTF-8' standalone='no'?>
			<svg height='100' width='100'>
				<defs>
					<linearGradient id='grad2' x1='0%' y1='0%' x2='100%' y2='100%'>
						<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
						<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
						<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
					</linearGradient>
				</defs>
				<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
			</svg>
			""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag1.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag1.png"));
	}

	@Test
	public void testTestGradientLinearDiag1Partiel() {
		//@formatter:off
		final String data = """
			<?xml version='1.0' encoding='UTF-8' standalone='no'?>
			<svg height='100' width='100'>
				<defs>
					<linearGradient id='grad2' x1='40%' y1='40%' x2='70%' y2='70%'>
						<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
						<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
					</linearGradient>
				</defs>
				<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
			</svg>
			""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag1Partiel.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag1Partiel.png"));
	}

	@Test
	public void testTestGradientLinearDiag2() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2.png"));
	}

	@Test
	public void testTestGradientLinearDiag2Rotate0() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='50%' x2='100%' y2='50%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse transform='rotate (30 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2Rotate0.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2Rotate0.png"));
	}

	@Test
	public void testTestGradientLinearDiag2Rotate1() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse transform='rotate (45 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2Rotate1.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2Rotate1.png"));
	}

	@Test
	public void testTestGradientLinearDiag2Rotate2() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse transform='rotate (-45 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2Rotate2.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2Rotate2.png"));
	}

	@Test
	public void testTestGradientLinearDiag2scale() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse transform='scale (0.5 2.0) translate (10,-25)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri
				.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2scale.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLineardiag2scale.png"));
	}

	@Test
	public void testTestGradientLinearHorizontal() {
		//@formatter:off
		final String data = """
			<?xml version='1.0' encoding='UTF-8' standalone='no'?>
			<svg height='100' width='100'>
				<defs>
					<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='0%'>
						<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
						<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
						<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
					</linearGradient>
				</defs>
				<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
			</svg>
			""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri
				.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLinearhorizontal.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearhorizontal.png"));
	}

	@Test
	public void testTestGradientLinearInternalHref() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2Values'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
						<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%' xlink:href='#grad2Values' />
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearinternalHref.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearinternalHref.png"));
	}

	@Test
	public void testTestGradientLinearUnitBoxspreadNone() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%'>
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadNone.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadNone.png"));
	}

	@Test
	public void testTestGradientLinearUnitBoxspreadPad() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='pad'>
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadPad.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadPad.png"));
	}

	@Test
	public void testTestGradientLinearUnitBoxspreadReflect() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='reflect'>
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadReflect.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadReflect.png"));
	}

	@Test
	public void testTestGradientLinearUnitBoxspreadRepeat() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='repeat'>
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadRepeat.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitBoxspreadRepeat.png"));
	}

	@Test
	public void testTestGradientLinearUnitUserspreadNone() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' gradientUnits='userSpaceOnUse'>
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadNone.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadNone.png"));
	}

	@Test
	public void testTestGradientLinearUnitUserspreadPad() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='pad' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadPad.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadPad.png"));
	}

	@Test
	public void testTestGradientLinearUnitUserspreadReflect() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadReflect.svg"),
						data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadReflect.png"));
	}

	@Test
	public void testTestGradientLinearUnitUserspreadRepeate() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadRepeate.svg"),
						data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearunitUserspreadRepeate.png"));
	}

	@Test
	public void testTestGradientLinearVertical() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='0%' x2='0%' y2='100%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri
				.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientLinearvertical.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientLinearvertical.png"));
	}
}

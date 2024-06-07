package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestGradientRadial {
	@Test
	public void testTestGradientRadialCircle() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='50' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialcircle.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialcircle.png"));
	}

	@Test
	public void testTestGradientRadialFull() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialfull.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialfull.png"));
	}

	@Test
	public void testTestGradientRadialPartial() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad2' cx='20%' cy='30%' r='30%' fx='50%' fy='50%'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri
				.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialpartial.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialpartial.png"));
	}

	@Test
	public void testTestGradientRadialUnitBoxspreadNone() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadNone.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadNone.png"));
	}

	@Test
	public void testTestGradientRadialUnitBoxspreadPad() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='pad'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadPad.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadPad.png"));
	}

	@Test
	public void testTestGradientRadialUnitBoxspreadReflect() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='reflect'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadReflect.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadReflect.png"));
	}

	@Test
	public void testTestGradientRadialUnitBoxspreadRepeat() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='repeat'>
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadRepeat.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitBoxspreadRepeat.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadNone() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50%' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadNone.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadNone.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadPad() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='pad' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadPad.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadPad.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadPadunCenter() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='pad' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadPadunCenter.svg"),
						data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc,
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadPadunCenter.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadReflect() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadReflect.svg"),
						data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadReflect.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadReflectunCenter() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadReflectunCenter.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc,
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadReflectunCenter.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadRepeat() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeat.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeat.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadRepeatout() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='24' fx='20' fy='40' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeatout.svg"),
						data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc,
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeatout.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadRepeatunCenter() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeatunCenter.svg"),
						data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc,
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeatunCenter.png"));
	}

	@Test
	public void testTestGradientRadialUnitUserspreadRepeatunCenter2() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad1' cx='50' cy='50' r='24' fx='60' fy='60' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >
							<stop offset='0%' style='stop-color:orange;stop-opacity:1' />
							<stop offset='45%' style='stop-color:red;stop-opacity:1' />
							<stop offset='55%' style='stop-color:blue;stop-opacity:1' />
							<stop offset='100%' style='stop-color:green;stop-opacity:1' />
						</radialGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />
				</svg>
				""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeatunCenter2.svg"),
				data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc,
				new Uri(ConfigTest.BASE_PATH + "TestGradientRadialunitUserspreadRepeatunCenter2.png"));
	}

}
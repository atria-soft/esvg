package test.atriasoft.esvg;

import org.atriasoft.esvg.Esvg;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.EsvgFont;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestFont {

	@Test
	public void testFontError1() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='900' width='700'>\
					<path d='M296 463q80 0 125 -45t45 -126q0 -130 -73 -217.5t-187 -87.5q-80 0 -125 45.5t-45 127.5q0 126 73 214.5t187 88.5zM218 51q78 0 123.5 68t45.5 166q0 115 -103 115q-75 0 -122 -66.5t-47 -167.5q0 -115 103 -115z'\
					      stroke='green' stroke-width='3' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestFontError1.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestFontError1.png"));
	}

	@Test
	public void testFontError2() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='900' width='700'>\
					<path d='M296 463q80 0 125 -45t45 -126q0 -130 -73 -217.5t-187 -87.5q-80 0 -125 45.5t-45 127.5q0 126 73 214.5t187 88.5z'\
					      stroke='green' stroke-width='3' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestFontError2.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestFontError2.png"));
	}

	@Test
	public void testFontError3() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='900' width='700'>\
					<path d='M218 51q78 0 123.5 68t45.5 166q0 115 -103 115q-75 0 -122 -66.5t-47 -167.5q0 -115 103 -115z'\
					      stroke='green' stroke-width='3' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestFontError3.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestFontError3.png"));
	}

	@Test
	public void testFontError4() {
		final String data = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>\
				<svg height='900' width='700'>\
					<path d='M1011 -78q51 -11 84.5 -50.5t33.5 -93.5q0 -61 -43 -103t-104 -42q-60 0 -102 43q-43 42 -43 102q0 34 16 67q-2 0 -20 -4.5t-36.5 -8t-47 -7.5t-66.5 -6.5t-80 -2.5q-144 0 -248 27.5t-164.5 80.5t-88.5 123t-28 161q0 124 106 240l33 -30q-101 -101 -101 -206
				q0 -335 487 -335q304 0 401 123q-39 -10 -68 -10q-95 3 -142 74q-50 -74 -136 -74q-68 0 -120 47t-52 125v92q0 75 -25.5 106t-58.5 31q-49 0 -92 -49t-43 -124q0 -19 3.5 -40.5t13.5 -53t34 -61.5t60 -48l-22 -25q-43 23 -72 58t-41 72.5t-16 63t-4 46.5q0 103 58.5 161.5
				t130.5 58.5q24 0 47.5 -8t46.5 -26.5t37 -56t14 -89.5v-87q0 -79 37 -112t81 -33q40 0 69.5 22.5t29.5 57.5v322h83v-275q0 -55 27.5 -84.5t67.5 -29.5q60 0 95.5 52.5t35.5 125.5q0 20 -3 40t-12.5 50t-33 57.5t-57.5 46.5l29 25q57 -44 90.5 -105t33.5 -130
				q0 -195 -115 -291zM972 -218q23 0 37.5 15t14.5 37q0 17 -16 32.5t-35 15.5q-30 0 -41.5 -12t-11.5 -36q0 -23 15 -37.5t37 -14.5zM970 -316q41 0 69.5 29t28.5 69q0 38 -19 60q1 -3 1 -13q0 -38 -25 -62.5t-60 -24.5q-33 0 -57.5 22.5t-28.5 55.5q-7 -20 -7 -38
				q0 -41 29 -69.5t69 -28.5z'\
					      stroke='green' stroke-width='3' />\
				</svg>""";
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestFontError4.svg"), data.replace("'", "\"")));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestFontError4.png"));
	}

	@Test
	public void testFontprintE25() {
		Esvg.init();
		final EsvgFont font = EsvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		Weight out = font.render('E', 25);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_E25.png"));
		out = font.render('e', 25);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_e25.png"));
		out = font.render('É', 25);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_Ecute25.png"));
		out = font.render('é', 25);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_ecute25.png"));
		out = font.render('p', 25);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_p25.png"));
		out = font.render('f', 25);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_f25.png"));
	}

	@Test
	public void testFontprintSimpleText() {
		Esvg.init();
		final EsvgFont font = EsvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Weight out = font.render("Hello, How are you? VA // @ ê É", 100, false);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_Hello.png"));
		out = font.render("Hello, How are you? VA // @ ê É", 100, true);
		ConfigTest.generateAnImage(out, new Uri(ConfigTest.BASE_PATH + "testFontprint_Hello_withKerning.png"));

	}

	@Test
	public void testFontRead() {
		Esvg.init();
		final EsvgFont font = EsvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));

	}
}
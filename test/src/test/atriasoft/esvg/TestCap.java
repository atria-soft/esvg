package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestCap {
	@Test
	public void testTestCapButt() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,75 80,75' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='80,25 20,25' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapbutt.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapbutt.png"));
	}
	
	@Test
	public void testTestCapButtDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 80,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='80,20 20,80' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapbuttDiag1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapbuttDiag1.png"));
	}
	
	@Test
	public void testTestCapButtDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 80,20' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='80,80 20,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapbuttDiag2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapbuttDiag2.png"));
	}
	
	@Test
	public void testTestCapButtVert() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='25,20 25,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='75,80 75,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapbuttVert.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapbuttVert.png"));
	}
	
	@Test
	public void testTestCapRound() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,75 80,75' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='80,25 20,25' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapround.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapround.png"));
	}
	
	@Test
	public void testTestCapRoundDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 80,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='80,20 20,80' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCaproundDiag1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCaproundDiag1.png"));
	}
	
	@Test
	public void testTestCapRoundDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 80,20' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='80,80 20,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCaproundDiag2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCaproundDiag2.png"));
	}
	
	@Test
	public void testTestCapRoundVert() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='25,20 25,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='75,80 75,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCaproundVert.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCaproundVert.png"));
	}
	
	@Test
	public void testTestCapSquare() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,75 80,75' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='80,25 20,25' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapsquare.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapsquare.png"));
	}
	
	@Test
	public void testTestCapSquareDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 80,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='80,20 20,80' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapsquareDiag1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapsquareDiag1.png"));
	}
	
	@Test
	public void testTestCapSquareDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 80,20' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='80,80 20,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapsquareDiag2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapsquareDiag2.png"));
	}
	
	@Test
	public void testTestCapSquareVert() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='25,20 25,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='75,80 75,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestCapsquareVert.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestCapsquareVert.png"));
	}
}

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
		Uri.writeAll(new Uri("TestCapbutt.svg"), data);
		doc.generateAnImage(new Uri("TestCapbutt.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapButtDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 80,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='80,20 20,80' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapbuttDiag1.svg"), data);
		doc.generateAnImage(new Uri("TestCapbuttDiag1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapButtDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 80,20' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='80,80 20,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapbuttDiag2.svg"), data);
		doc.generateAnImage(new Uri("TestCapbuttDiag2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapButtVert() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='25,20 25,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
				+ "	<polyline points='75,80 75,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='butt'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapbuttVert.svg"), data);
		doc.generateAnImage(new Uri("TestCapbuttVert.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapRound() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,75 80,75' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='80,25 20,25' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapround.svg"), data);
		doc.generateAnImage(new Uri("TestCapround.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapRoundDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 80,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='80,20 20,80' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCaproundDiag1.svg"), data);
		doc.generateAnImage(new Uri("TestCaproundDiag1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapRoundDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 80,20' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='80,80 20,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCaproundDiag2.svg"), data);
		doc.generateAnImage(new Uri("TestCaproundDiag2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapRoundVert() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='25,20 25,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
				+ "	<polyline points='75,80 75,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCaproundVert.svg"), data);
		doc.generateAnImage(new Uri("TestCaproundVert.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapSquare() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,75 80,75' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='80,25 20,25' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapsquare.svg"), data);
		doc.generateAnImage(new Uri("TestCapsquare.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapSquareDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 80,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='80,20 20,80' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapsquareDiag1.svg"), data);
		doc.generateAnImage(new Uri("TestCapsquareDiag1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapSquareDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 80,20' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='80,80 20,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapsquareDiag2.svg"), data);
		doc.generateAnImage(new Uri("TestCapsquareDiag2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestCapSquareVert() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='25,20 25,80' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
				+ "	<polyline points='75,80 75,20' stroke='orange' stroke-width='20' fill='none' stroke-linecap='square'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestCapsquareVert.svg"), data);
		doc.generateAnImage(new Uri("TestCapsquareVert.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}

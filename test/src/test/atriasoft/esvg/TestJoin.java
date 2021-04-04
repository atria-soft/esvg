package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestJoin {
	@Test
	public void testTestJoinBevelCornerCasePath() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelCornerCasePath.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelCornerCasePath.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelLeft1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelLeft1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelLeft1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelLeft2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelLeft2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelLeft2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelLeft3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelLeft3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelLeft3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelLeft4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelLeft4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelLeft4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelRight1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelRight1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelRight1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelRight2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelRight2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelRight2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelRight3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelRight3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelRight3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinBevelRight4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinbevelRight4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinbevelRight4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterCornerCasePath() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterCornerCasePath.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterCornerCasePath.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterCornerCasePathLimit() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='miter' stroke-miterlimit='0.3'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterCornerCasePathLimit.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterCornerCasePathLimit.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLeft1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLeft1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLeft1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLeft2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLeft2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLeft2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLeft3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLeft3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLeft3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	// ------------------------------------------------------ Round test -----------------------------------------------------
	
	@Test
	public void testTestJoinMiterLeft4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLeft4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLeft4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLimit1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 25,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLimit1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLimit1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLimit2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 50,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLimit2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLimit2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLimit3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 75,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLimit3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLimit3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterLimit4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 90,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterLimit4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterLimit4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterRight1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterRight1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterRight1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterRight2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterRight2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterRight2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterRight3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterRight3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterRight3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinMiterRight4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinmiterRight4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinmiterRight4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	// ------------------------------------------------------ Bevel test -----------------------------------------------------
	
	@Test
	public void testTestJoinRoundCornerCasePath() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundCornerCasePath.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundCornerCasePath.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundLeft1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundLeft1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundLeft1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundLeft2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundLeft2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundLeft2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundLeft3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundLeft3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundLeft3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundLeft4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundLeft4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundLeft4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundRight1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundRight1.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundRight1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundRight2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundRight2.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundRight2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundRight3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundRight3.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundRight3.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestJoinRoundRight4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestJoinroundRight4.svg"), data);
		doc.generateAnImage(new Uri("TestJoinroundRight4.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}

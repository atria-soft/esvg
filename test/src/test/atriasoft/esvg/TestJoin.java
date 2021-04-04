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
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelCornerCasePath.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelCornerCasePath.png"));
	}
	
	@Test
	public void testTestJoinBevelLeft1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft1.png"));
	}
	
	@Test
	public void testTestJoinBevelLeft2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft2.png"));
	}
	
	@Test
	public void testTestJoinBevelLeft3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft3.png"));
	}
	
	@Test
	public void testTestJoinBevelLeft4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelLeft4.png"));
	}
	
	@Test
	public void testTestJoinBevelRight1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight1.png"));
	}
	
	@Test
	public void testTestJoinBevelRight2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight2.png"));
	}
	
	@Test
	public void testTestJoinBevelRight3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight3.png"));
	}
	
	@Test
	public void testTestJoinBevelRight4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinbevelRight4.png"));
	}
	
	@Test
	public void testTestJoinMiterCornerCasePath() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterCornerCasePath.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterCornerCasePath.png"));
	}
	
	@Test
	public void testTestJoinMiterCornerCasePathLimit() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='miter' stroke-miterlimit='0.3'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterCornerCasePathLimit.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterCornerCasePathLimit.png"));
	}
	
	@Test
	public void testTestJoinMiterLeft1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft1.png"));
	}
	
	@Test
	public void testTestJoinMiterLeft2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft2.png"));
	}
	
	@Test
	public void testTestJoinMiterLeft3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft3.png"));
	}
	
	// ------------------------------------------------------ Round test -----------------------------------------------------
	
	@Test
	public void testTestJoinMiterLeft4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLeft4.png"));
	}
	
	@Test
	public void testTestJoinMiterLimit1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 25,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit1.png"));
	}
	
	@Test
	public void testTestJoinMiterLimit2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 50,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit2.png"));
	}
	
	@Test
	public void testTestJoinMiterLimit3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 75,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit3.png"));
	}
	
	@Test
	public void testTestJoinMiterLimit4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='10,10 90,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterLimit4.png"));
	}
	
	@Test
	public void testTestJoinMiterRight1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight1.png"));
	}
	
	@Test
	public void testTestJoinMiterRight2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight2.png"));
	}
	
	@Test
	public void testTestJoinMiterRight3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight3.png"));
	}
	
	@Test
	public void testTestJoinMiterRight4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinmiterRight4.png"));
	}
	
	// ------------------------------------------------------ Bevel test -----------------------------------------------------
	
	@Test
	public void testTestJoinRoundCornerCasePath() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "    <path"
				+ "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
				+ "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundCornerCasePath.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundCornerCasePath.png"));
	}
	
	@Test
	public void testTestJoinRoundLeft1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft1.png"));
	}
	
	@Test
	public void testTestJoinRoundLeft2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft2.png"));
	}
	
	@Test
	public void testTestJoinRoundLeft3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft3.png"));
	}
	
	@Test
	public void testTestJoinRoundLeft4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundLeft4.png"));
	}
	
	@Test
	public void testTestJoinRoundRight1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight1.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight1.png"));
	}
	
	@Test
	public void testTestJoinRoundRight2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight2.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight2.png"));
	}
	
	@Test
	public void testTestJoinRoundRight3() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight3.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight3.png"));
	}
	
	@Test
	public void testTestJoinRoundRight4() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight4.svg"), data.replace("'", "\""));
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "TestJoinroundRight4.png"));
	}
}

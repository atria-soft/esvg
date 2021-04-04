package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestGradientLinear {
	@Test
	public void testTestGradientLinearDiag1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='0%' x2='100%' y2='100%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag1.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearDiag1Partiel() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='40%' y1='40%' x2='70%' y2='70%'>\n" + "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag1Partiel.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag1Partiel.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearDiag2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag2.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearDiag2Rotate0() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='50%' x2='100%' y2='50%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse transform='rotate (30 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag2Rotate0.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag2Rotate0.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearDiag2Rotate1() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse transform='rotate (45 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag2Rotate1.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag2Rotate1.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearDiag2Rotate2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse transform='rotate (-45 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag2Rotate2.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag2Rotate2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearDiag2scale() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse transform='scale (0.5 2.0) translate (10,-25)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLineardiag2scale.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLineardiag2scale.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearHorizontal() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='0%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearhorizontal.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearhorizontal.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearInternalHref() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n" + "		<linearGradient id='grad2Values'>\n"
				+ "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
				+ "		</linearGradient>\n" + "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%' xlink:href='#grad2Values' />\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearinternalHref.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearinternalHref.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitBoxspreadNone() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%'>\n" + "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitBoxspreadNone.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitBoxspreadNone.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitBoxspreadPad() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='pad'>\n" + "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitBoxspreadPad.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitBoxspreadPad.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitBoxspreadReflect() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='reflect'>\n" + "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitBoxspreadReflect.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitBoxspreadReflect.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitBoxspreadRepeat() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='repeat'>\n" + "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitBoxspreadRepeat.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitBoxspreadRepeat.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitUserspreadNone() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' gradientUnits='userSpaceOnUse'>\n"
				+ "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "		</linearGradient>\n" + "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitUserspreadNone.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitUserspreadNone.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitUserspreadPad() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='pad' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "		</linearGradient>\n" + "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitUserspreadPad.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitUserspreadPad.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitUserspreadReflect() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "		</linearGradient>\n" + "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitUserspreadReflect.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitUserspreadReflect.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearUnitUserspreadRepeate() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "		</linearGradient>\n" + "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearunitUserspreadRepeate.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearunitUserspreadRepeate.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientLinearVertical() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<linearGradient id='grad2' x1='0%' y1='0%' x2='0%' y2='100%'>\n" + "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n" + "		</linearGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientLinearvertical.svg"), data);
		doc.generateAnImage(new Uri("TestGradientLinearvertical.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}

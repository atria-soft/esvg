package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestGradientRadial {
	@Test
	public void testTestGradientRadialCircle() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='50' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialcircle.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialcircle.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialFull() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialfull.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialfull.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialPartial() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad2' cx='20%' cy='30%' r='30%' fx='50%' fy='50%'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialpartial.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialpartial.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitBoxspreadNone() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitBoxspreadNone.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitBoxspreadNone.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitBoxspreadPad() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='pad'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitBoxspreadPad.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitBoxspreadPad.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitBoxspreadReflect() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='reflect'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitBoxspreadReflect.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitBoxspreadReflect.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitBoxspreadRepeat() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='repeat'>\n" + "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
				+ "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n" + "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
				+ "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n" + "	</defs>\n"
				+ "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitBoxspreadRepeat.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitBoxspreadRepeat.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadNone() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50%' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadNone.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadNone.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadPad() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='pad' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadPad.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadPad.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadPadunCenter() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='pad' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadPadunCenter.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadPadunCenter.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadReflect() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadReflect.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadReflect.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadReflectunCenter() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadReflectunCenter.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadReflectunCenter.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadRepeat() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadRepeat.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadRepeat.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadRepeatout() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='20' fy='40' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadRepeatout.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadRepeatout.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadRepeatunCenter() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadRepeatunCenter.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadRepeatunCenter.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestGradientRadialUnitUserspreadRepeatunCenter2() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" + "<svg height='100' width='100'>\n" + "	<defs>\n"
				+ "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='60' fy='60' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
				+ "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n" + "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
				+ "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n" + "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n" + "		</radialGradient>\n"
				+ "	</defs>\n" + "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n" + "</svg>\n";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestGradientRadialunitUserspreadRepeatunCenter2.svg"), data);
		doc.generateAnImage(new Uri("TestGradientRadialunitUserspreadRepeatunCenter2.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
}
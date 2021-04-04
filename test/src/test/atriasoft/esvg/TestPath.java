package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Test;

class TestPath {
	@Test
	public void testTestPathArc() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='300' width='800'>" + "	<path d='M20,290 l 50,-25" + "	      a25,25 -30 0,1 50,-25 l 30,0"
				+ "	      a25,50 -30 0,0 40,-25 l 30,0" + "	      a25,50 -30 0,0 50,-25 l 30,0" + "	      a25,75 -30 0,1 50,-25 l 30,0" + "	      a25,100 30 1,0 50,-25 l 30,0"
				+ "	      a25,100 30 0,0 50,-25 l 30,0" + "	      a25,100 30 0,1 50,-25 l 30,0" + "	      a25,100 30 1,1 50,-25 l 30,0'" + "	      fill='none' stroke='red' stroke-width='5' />"
				+ "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPatharc.svg"), data);
		doc.generateAnImage(new Uri("TestPatharc.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathBezierCurveTo() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<path d='m 50,50 q -30,1 -20,20 z'" + "	      fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathbezierCurveTo.svg"), data);
		doc.generateAnImage(new Uri("TestPathbezierCurveTo.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathBezierSmoothCurveTo() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<path d='m 50,50 t -20,30 t 30,-20 z'" + "	      fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathbezierSmoothCurveTo.svg"), data);
		doc.generateAnImage(new Uri("TestPathbezierSmoothCurveTo.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathCurveTo() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<path d='m 50,50 c -30,0 -30,1 -20,20 z'" + "	      fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathcurveTo.svg"), data);
		doc.generateAnImage(new Uri("TestPathcurveTo.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathEndpathbordercase() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<path\n"
				+ "	   style='fill:#9fecff;fill-opacity:1;stroke:#1b57df;stroke-width:8.81125546;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:0.94901961'\n"
				+ "	   d='M 83.073072,55.099829 C 83.886712,33.687876 60.475404,16.478179 40.263655,23.556532 19.565051,29.111554 9.9926694,56.534855 22.756336,73.74319 c 11.428293,18.124001 40.474216,19.151787 53.156943,1.880953 4.612608,-5.778118 7.177805,-13.13422 7.159793,-20.524314 z'\n"
				+ "	   id='path3421'\n" + "	   inkscape:connector-curvature='0' />\n" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathendpathbordercase.svg"), data);
		doc.generateAnImage(new Uri("TestPathendpathbordercase.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathfill() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
				+ "	      fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathfill.svg"), data);
		doc.generateAnImage(new Uri("TestPathfill.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathFillandstroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
				+ "	      stroke='green' stroke-width='3' fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathfillandstroke.svg"), data);
		doc.generateAnImage(new Uri("TestPathfillandstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathSmoothCurveTo() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>" + "	<path d='m 50,50 s -30,0 -20,20 z'" + "	      fill='red' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathsmoothCurveTo.svg"), data);
		doc.generateAnImage(new Uri("TestPathsmoothCurveTo.bmp"), ConfigTest.VISUAL_DEBUG);
	}
	
	@Test
	public void testTestPathStroke() {
		String data = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>" + "<svg height='100' width='100'>"
				+ "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
				+ "	      stroke='green' stroke-width='3' />" + "</svg>";
		EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		Uri.writeAll(new Uri("TestPathstroke.svg"), data);
		doc.generateAnImage(new Uri("TestPathstroke.bmp"), ConfigTest.VISUAL_DEBUG);
	}
}
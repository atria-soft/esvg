/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.h>
#include "main.h"

#undef __class__
#define __class__	"TestPath"

TEST(TestPath, fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	                 "	      fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_fill.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_fill.bmp", g_visualDebug);
}

TEST(TestPath, stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	                 "	      stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_stroke.bmp", g_visualDebug);
}

TEST(TestPath, fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	                 "	      stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_fill_and_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_fill_and_stroke.bmp", g_visualDebug);
}

TEST(TestPath, curveTo) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 c -30,0 -30,1 -20,20 z'"
	                 "	      fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_curveTo.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_curveTo.bmp", g_visualDebug);
}



TEST(TestPath, smoothCurveTo) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 s -30,0 -20,20 z'"
	                 "	      fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_smoothCurveTo.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_smoothCurveTo.bmp", g_visualDebug);
}



TEST(TestPath, bezierCurveTo) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 q -30,1 -20,20 z'"
	                 "	      fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_bezierCurveTo.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_bezierCurveTo.bmp", g_visualDebug);
}



TEST(TestPath, bezierSmoothCurveTo) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path d='m 50,50 t -20,30 t 30,-20 z'"
	                 "	      fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_bezierSmoothCurveTo.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_bezierSmoothCurveTo.bmp", g_visualDebug);
}

TEST(TestPath, arc) {
	// TODO : ...
	EXPECT_EQ(1, 2);
}




TEST(TestPath, end_path_border_case) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<path\n"
	                 "	   style='fill:#9fecff;fill-opacity:1;stroke:#1b57df;stroke-width:8.81125546;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:0.94901961'\n"
	                 "	   d='M 83.073072,55.099829 C 83.886712,33.687876 60.475404,16.478179 40.263655,23.556532 19.565051,29.111554 9.9926694,56.534855 22.756336,73.74319 c 11.428293,18.124001 40.474216,19.151787 53.156943,1.880953 4.612608,-5.778118 7.177805,-13.13422 7.159793,-20.524314 z'\n"
	                 "	   id='path3421'\n"
	                 "	   inkscape:connector-curvature='0' />\n"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPath_end_path_border_case.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestPath_end_path_border_case.bmp", g_visualDebug);
}
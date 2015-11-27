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

/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestPolyLine, fill) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 40,25 60,40 80,90 90,50 5,90' fill='orange' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPolyLine_fill.svg", data);
	doc.generateAnImage("TestPolyLine_fill.bmp", g_visualDebug);
}

TEST(TestPolyLine, stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 40,25 60,40 80,90 90,50 5,90' stroke='green' stroke-width='3' fill='none' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPolyLine_stroke.svg", data);
	doc.generateAnImage("TestPolyLine_stroke.bmp", g_visualDebug);
}

TEST(TestPolyLine, fill_and_stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 40,25 60,40 80,90 90,50 5,90' stroke='green' stroke-width='3' fill='orange' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPolyLine_fill_and_stroke.svg", data);
	doc.generateAnImage("TestPolyLine_fill_and_stroke.bmp", g_visualDebug);
}



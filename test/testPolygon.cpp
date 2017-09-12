/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestPolygon, fill) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polygon points='50,10 90,50 10,80' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPolygon_fill.svg", data);
	doc.generateAnImage("TestPolygon_fill.bmp", g_visualDebug);
}

TEST(TestPolygon, stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polygon points='50,10 90,50 10,80' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPolygon_stroke.svg", data);
	doc.generateAnImage("TestPolygon_stroke.bmp", g_visualDebug);
}

TEST(TestPolygon, fill_and_stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polygon points='50,10 90,50 10,80' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestPolygon_fill_and_stroke.svg", data);
	doc.generateAnImage("TestPolygon_fill_and_stroke.bmp", g_visualDebug);
}
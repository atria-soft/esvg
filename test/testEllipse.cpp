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

TEST(TestEllipse, fill) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<ellipse cx='50' cy='50' rx='80' ry='30' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestEllipse_fill.svg", data);
	doc.generateAnImage("TestEllipse_fill.bmp", g_visualDebug);
}

TEST(TestEllipse, stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<ellipse cx='50' cy='50' rx='80' ry='30' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestEllipse_stroke.svg", data);
	doc.generateAnImage("TestEllipse_stroke.bmp", g_visualDebug);
}

TEST(TestEllipse, fill_and_stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<ellipse cx='50' cy='50' rx='80' ry='30' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestEllipse_fill_and_stroke.svg", data);
	doc.generateAnImage("TestEllipse_fill_and_stroke.bmp", g_visualDebug);
}


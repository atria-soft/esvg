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
#define __class__	"TestEllipse"

TEST(TestEllipse, fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<ellipse cx='50' cy='50' rx='80' ry='30' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestEllipse_fill.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestEllipse_fill.bmp", g_visualDebug);
}

TEST(TestEllipse, stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<ellipse cx='50' cy='50' rx='80' ry='30' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestEllipse_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestEllipse_stroke.bmp", g_visualDebug);
}

TEST(TestEllipse, fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<ellipse cx='50' cy='50' rx='80' ry='30' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestEllipse_fill_and_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestEllipse_fill_and_stroke.bmp", g_visualDebug);
}


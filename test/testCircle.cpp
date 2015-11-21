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
#define __class__	"TestCircle"

TEST(TestCircle, fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<circle cx='50' cy='50' r='40' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestCircle_fill.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestCircle_fill.ppm", g_visualDebug);
}

TEST(TestCircle, stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestCircle_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestCircle_stroke.ppm", g_visualDebug);
}

TEST(TestCircle, fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestCircle_fill_and_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestCircle_fill_and_stroke.ppm", g_visualDebug);
}

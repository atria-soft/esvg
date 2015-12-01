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
#define __class__	"TestRectangle"

TEST(TestRectangle, fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_fill.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill.bmp", g_visualDebug);
}

TEST(TestRectangle, stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_stroke.bmp", g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_fill_and_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill_and_stroke.bmp", g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke_blend) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_fill_and_stroke_blend.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill_and_stroke_blend.bmp", g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke_opacity) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-width='3' fill='#F00' opacity='0.5' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_fill_and_stroke_opacity.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill_and_stroke_opacity.bmp", g_visualDebug);
}

TEST(TestRectangle, corned_fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_corned_fill.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_corned_fill.bmp", g_visualDebug);
}

TEST(TestRectangle, corned_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_corned_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_corned_stroke.bmp", g_visualDebug);
}

TEST(TestRectangle, corned_fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_corned_fill_and_stroke.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_corned_fill_and_stroke.bmp", g_visualDebug);
}

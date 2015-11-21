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
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill.ppm", g_visualDebug);
}

TEST(TestRectangle, stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_stroke.ppm", g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill_and_stroke.ppm", g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke_blend) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F08' stroke-width='3' fill='#F008' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_fill_and_stroke_blend.ppm", g_visualDebug);
}

TEST(TestRectangle, corned_fill) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_corned_fill.ppm", g_visualDebug);
}

TEST(TestRectangle, corned_stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_corned_stroke.ppm", g_visualDebug);
}

TEST(TestRectangle, corned_fill_and_stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestRectangle_corned_fill_and_stroke.ppm", g_visualDebug);
}

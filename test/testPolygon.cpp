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
#define __class__	"TestPolygon"

TEST(TestPolygon, fill) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<polygon points='50,10 90,50 10,80' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestPolygon_fill.ppm", g_visualDebug);
}

TEST(TestPolygon, stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<polygon points='50,10 90,50 10,80' stroke='green' stroke-width='3' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestPolygon_stroke.ppm", g_visualDebug);
}

TEST(TestPolygon, fill_and_stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<polygon points='50,10 90,50 10,80' stroke='green' stroke-width='3' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestPolygon_fill_and_stroke.ppm", g_visualDebug);
}
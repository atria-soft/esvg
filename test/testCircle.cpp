/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.h>

TEST(TestCircle, fill) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<circle cx='50' cy='50' r='40' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestCircle_fill.ppm");
}

TEST(TestCircle, stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestCircle_stroke.ppm");
}

TEST(TestCircle, fill_and_stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestCircle_fill_and_stroke.ppm");
}

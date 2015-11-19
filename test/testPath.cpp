/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.h>
/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.h>

TEST(TestPath, fill) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	           "	      fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestPath_fill.ppm");
}

TEST(TestPath, stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	           "	      stroke='green' stroke-width='3' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestPath_stroke.ppm");
}

TEST(TestPath, fill_and_stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	           "	      stroke='green' stroke-width='3' fill='red' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestPath_fill_and_stroke.ppm");
}

/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.h>

TEST(TestLine, stroke) {
	esvg::Document doc;
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg height='100' width='100'>"
	           "	<line x1='10' y1='10' x2='90' y2='90' stroke='green' stroke-width='3' />"
	           "</svg>");
	doc.generateAnImage(ivec2(100, 100), "TestLine_stroke.ppm");
}
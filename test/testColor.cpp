/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestColor, blending) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestColor_blending.svg"), data);
	doc.generateAnImage(etk::Path("TestColor_blending.bmp"), g_visualDebug);
}

TEST(TestColor, opacity) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-width='3' fill='#F00' opacity='0.5' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestColor_opacity.svg"), data);
	doc.generateAnImage(etk::Path("TestColor_opacity.bmp"), g_visualDebug);
}

TEST(TestColor, blending_and_opacity) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' opacity='0.7' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestColor_blending_and_opacity.svg"), data);
	doc.generateAnImage(etk::Path("TestColor_blending_and_opacity.bmp"), g_visualDebug);
}

TEST(TestColor, multiple_layer) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='50'   y='5' width='15' height='75' stroke='blue' stroke-width='9' fill='green'/>"
	                 "	<rect x='12.5' y='12.5' width='75' height='30' stroke='#0F0' stroke-opacity='0.5' stroke-width='3' fill='#F00' fill-opacity='0.5' opacity='0.7' />"
	                 "	<rect x='30'   y='30' width='20' height='20' stroke='orange' stroke-width='1' fill='violet'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestColor_multiple_layer.svg"), data);
	doc.generateAnImage(etk::Path("TestColor_multiple_layer.bmp"), g_visualDebug);
}

/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestRectangle, fill) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestRectangle_fill.svg"), data);
	doc.generateAnImage(etk::Path("TestRectangle_fill.bmp"), g_visualDebug);
}

TEST(TestRectangle, stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestRectangle_stroke.svg"), data);
	doc.generateAnImage(etk::Path("TestRectangle_stroke.bmp"), g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestRectangle_fill_and_stroke.svg"), data);
	doc.generateAnImage(etk::Path("TestRectangle_fill_and_stroke.bmp"), g_visualDebug);
}

TEST(TestRectangle, corned_fill) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestRectangle_corned_fill.svg"), data);
	doc.generateAnImage(etk::Path("TestRectangle_corned_fill.bmp"), g_visualDebug);
}

TEST(TestRectangle, corned_stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestRectangle_corned_stroke.svg"), data);
	doc.generateAnImage(etk::Path("TestRectangle_corned_stroke.bmp"), g_visualDebug);
}

TEST(TestRectangle, corned_fill_and_stroke) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestRectangle_corned_fill_and_stroke.svg"), data);
	doc.generateAnImage(etk::Path("TestRectangle_corned_fill_and_stroke.bmp"), g_visualDebug);
}

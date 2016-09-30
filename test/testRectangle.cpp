/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestRectangle, fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_fill.svg", data);
	doc.generateAnImage("TestRectangle_fill.bmp", g_visualDebug);
}

TEST(TestRectangle, stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_stroke.svg", data);
	doc.generateAnImage("TestRectangle_stroke.bmp", g_visualDebug);
}

TEST(TestRectangle, fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_fill_and_stroke.svg", data);
	doc.generateAnImage("TestRectangle_fill_and_stroke.bmp", g_visualDebug);
}

TEST(TestRectangle, corned_fill) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_corned_fill.svg", data);
	doc.generateAnImage("TestRectangle_corned_fill.bmp", g_visualDebug);
}

TEST(TestRectangle, corned_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_corned_stroke.svg", data);
	doc.generateAnImage("TestRectangle_corned_stroke.bmp", g_visualDebug);
}

TEST(TestRectangle, corned_fill_and_stroke) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<rect x='12.5' y='12.5' width='75' height='50' rx='20' ry='20' stroke='green' stroke-width='3' fill='red' />"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestRectangle_corned_fill_and_stroke.svg", data);
	doc.generateAnImage("TestRectangle_corned_fill_and_stroke.bmp", g_visualDebug);
}

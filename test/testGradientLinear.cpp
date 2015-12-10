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
#define __class__	"TestGradientLinear"

TEST(TestGradientLinear, horizontal) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_horizontal.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientLinear_horizontal.bmp", g_visualDebug);
}


TEST(TestGradientLinear, vertical) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='0%' x2='0%' y2='100%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_vertical.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientLinear_vertical.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag1) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='0%' x2='100%' y2='100%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag1.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientLinear_diag1.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag2) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag2.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientLinear_diag2.bmp", g_visualDebug);
}



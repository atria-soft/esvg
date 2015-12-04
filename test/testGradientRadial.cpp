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
#define __class__	"TestGradientRadial"

TEST(TestGradientRadial, full) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,255,255);stop-opacity:0' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='200' cy='70' rx='85' ry='55' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_full.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_full.bmp", g_visualDebug);
}


TEST(TestGradientRadial, partial) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad2' cx='20%' cy='30%' r='30%' fx='50%' fy='50%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,255,255);stop-opacity:0' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='200' cy='70' rx='85' ry='55' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_partial.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_partial.bmp", g_visualDebug);
}
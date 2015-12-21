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

TEST(TestGradientRadial, circle) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='50' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_circle.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_circle.bmp", g_visualDebug);
}


TEST(TestGradientRadial, full) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='50%' fx='50%' fy='50%'>\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
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
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_partial.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_partial.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitBox_spreadNone) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%'>\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitBox_spreadNone.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitBox_spreadNone.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitBox_spreadPad) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='pad'>\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitBox_spreadPad.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitBox_spreadPad.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitBox_spreadReflect) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='reflect'>\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitBox_spreadReflect.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitBox_spreadReflect.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitBox_spreadRepeat) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50%' cy='50%' r='10%' fx='50%' fy='50%' spreadMethod='repeat'>\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitBox_spreadRepeat.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitBox_spreadRepeat.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitUser_spreadNone) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50%' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadNone.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitUser_spreadNone.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadPad) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='pad' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadPad.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitUser_spreadPad.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadReflect) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadReflect.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitUser_spreadReflect.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitUser_spreadRepeat) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='10' fx='50' fy='50' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:orange;stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:red;stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:blue;stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:green;stop-opacity:1' />\n"
	                 "		</radialGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadRepeat.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestGradientRadial_unitUser_spreadRepeat.bmp", g_visualDebug);
}



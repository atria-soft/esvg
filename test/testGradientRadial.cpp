/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestGradientRadial, circle) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_circle.bmp", g_visualDebug);
}


TEST(TestGradientRadial, full) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_full.bmp", g_visualDebug);
}


TEST(TestGradientRadial, partial) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_partial.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitBox_spreadNone) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitBox_spreadNone.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitBox_spreadPad) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitBox_spreadPad.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitBox_spreadReflect) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitBox_spreadReflect.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitBox_spreadRepeat) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitBox_spreadRepeat.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitUser_spreadNone) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitUser_spreadNone.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadPad) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitUser_spreadPad.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadReflect) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitUser_spreadReflect.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitUser_spreadRepeat) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
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
	doc.generateAnImage("TestGradientRadial_unitUser_spreadRepeat.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadPad_unCenter) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='pad' gradientUnits='userSpaceOnUse' >\n"
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
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadPad_unCenter.svg", data);
	doc.generateAnImage("TestGradientRadial_unitUser_spreadPad_unCenter.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadReflect_unCenter) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
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
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadReflect_unCenter.svg", data);
	doc.generateAnImage("TestGradientRadial_unitUser_spreadReflect_unCenter.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadRepeat_unCenter) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='40' fy='40' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
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
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadRepeat_unCenter.svg", data);
	doc.generateAnImage("TestGradientRadial_unitUser_spreadRepeat_unCenter.bmp", g_visualDebug);
}

TEST(TestGradientRadial, unitUser_spreadRepeat_unCenter2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='60' fy='60' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
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
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadRepeat_unCenter2.svg", data);
	doc.generateAnImage("TestGradientRadial_unitUser_spreadRepeat_unCenter2.bmp", g_visualDebug);
}


TEST(TestGradientRadial, unitUser_spreadRepeat_out) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<radialGradient id='grad1' cx='50' cy='50' r='24' fx='20' fy='40' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
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
	etk::FSNodeWriteAllData("TestGradientRadial_unitUser_spreadRepeat_out.svg", data);
	doc.generateAnImage("TestGradientRadial_unitUser_spreadRepeat_out.bmp", g_visualDebug);
}
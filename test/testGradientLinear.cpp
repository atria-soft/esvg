/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.hpp>
#include "main.hpp"

TEST(TestGradientLinear, horizontal) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad1)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_horizontal.svg", data);
	doc.generateAnImage("TestGradientLinear_horizontal.bmp", g_visualDebug);
}


TEST(TestGradientLinear, vertical) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='0%' x2='0%' y2='100%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_vertical.svg", data);
	doc.generateAnImage("TestGradientLinear_vertical.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='0%' x2='100%' y2='100%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag1.svg", data);
	doc.generateAnImage("TestGradientLinear_diag1.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag1Partiel) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='40%' y1='40%' x2='70%' y2='70%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag1Partiel.svg", data);
	doc.generateAnImage("TestGradientLinear_diag1Partiel.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag2.svg", data);
	doc.generateAnImage("TestGradientLinear_diag2.bmp", g_visualDebug);
}



TEST(TestGradientLinear, diag2Rotate0) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='50%' x2='100%' y2='50%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse transform='rotate (30 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag2Rotate0.svg", data);
	doc.generateAnImage("TestGradientLinear_diag2Rotate0.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag2Rotate1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse transform='rotate (45 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag2Rotate1.svg", data);
	doc.generateAnImage("TestGradientLinear_diag2Rotate1.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag2Rotate2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse transform='rotate (-45 50 50)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag2Rotate2.svg", data);
	doc.generateAnImage("TestGradientLinear_diag2Rotate2.bmp", g_visualDebug);
}

TEST(TestGradientLinear, diag2scale) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse transform='scale (0.5 2.0) translate (10,-25)' cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_diag2scale.svg", data);
	doc.generateAnImage("TestGradientLinear_diag2scale.bmp", g_visualDebug);
}

TEST(TestGradientLinear, internalHref) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2Values'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />\n"
	                 "			<stop offset='45%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='55%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(255,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "		<linearGradient id='grad2' x1='0%' y1='100%' x2='100%' y2='0%' xlink:href='#grad2Values' />\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)' />\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_internalHref.svg", data);
	doc.generateAnImage("TestGradientLinear_internalHref.bmp", g_visualDebug);
}


TEST(TestGradientLinear, unitBox_spreadNone) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitBox_spreadNone.svg", data);
	doc.generateAnImage("TestGradientLinear_unitBox_spreadNone.bmp", g_visualDebug);
}

TEST(TestGradientLinear, unitBox_spreadPad) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='pad'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitBox_spreadPad.svg", data);
	doc.generateAnImage("TestGradientLinear_unitBox_spreadPad.bmp", g_visualDebug);
}


TEST(TestGradientLinear, unitBox_spreadReflect) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='reflect'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitBox_spreadReflect.svg", data);
	doc.generateAnImage("TestGradientLinear_unitBox_spreadReflect.bmp", g_visualDebug);
}


TEST(TestGradientLinear, unitBox_spreadRepeat) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='40%' y1='40%' x2='60%' y2='60%' spreadMethod='repeat'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitBox_spreadRepeat.svg", data);
	doc.generateAnImage("TestGradientLinear_unitBox_spreadRepeat.bmp", g_visualDebug);
}

TEST(TestGradientLinear, unitUser_spreadNone) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' gradientUnits='userSpaceOnUse'>\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitUser_spreadNone.svg", data);
	doc.generateAnImage("TestGradientLinear_unitUser_spreadNone.bmp", g_visualDebug);
}

TEST(TestGradientLinear, unitUser_spreadPad) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='pad' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitUser_spreadPad.svg", data);
	doc.generateAnImage("TestGradientLinear_unitUser_spreadPad.bmp", g_visualDebug);
}


TEST(TestGradientLinear, unitUser_spreadReflect) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='reflect' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitUser_spreadReflect.svg", data);
	doc.generateAnImage("TestGradientLinear_unitUser_spreadReflect.bmp", g_visualDebug);
}


TEST(TestGradientLinear, unitUser_spreadRepeate) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
	                 "<svg height='100' width='100'>\n"
	                 "	<defs>\n"
	                 "		<linearGradient id='grad2' x1='45' y1='45' x2='55' y2='55' spreadMethod='repeat' gradientUnits='userSpaceOnUse' >\n"
	                 "			<stop offset='0%' style='stop-color:rgb(0,255,0);stop-opacity:1' />\n"
	                 "			<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />\n"
	                 "		</linearGradient>\n"
	                 "	</defs>\n"
	                 "	<ellipse cx='50' cy='50' rx='50' ry='20' fill='url(#grad2)'/>\n"
	                 "</svg>\n");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestGradientLinear_unitUser_spreadRepeate.svg", data);
	doc.generateAnImage("TestGradientLinear_unitUser_spreadRepeate.bmp", g_visualDebug);
}


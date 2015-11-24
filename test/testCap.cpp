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
#define __class__	"TestLine"

TEST(TestCap, butt) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,50 80,50' stroke='green' stroke-width='20' fill='none' stroke-linecap='butt'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestCap_butt.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestCap_butt.bmp", g_visualDebug);
}

TEST(TestCap, round) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,50 80,50' stroke='green' stroke-width='20' fill='none' stroke-linecap='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestCap_round.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestCap_round.bmp", g_visualDebug);
}

TEST(TestCap, square) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,50 80,50' stroke='green' stroke-width='20' fill='none' stroke-linecap='square'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestCap_square.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestCap_square.bmp", g_visualDebug);
}


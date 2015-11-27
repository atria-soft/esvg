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

TEST(TestJoin, miter) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestJoin_miter.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestJoin_miter.bmp", g_visualDebug);
}

TEST(TestJoin, round) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestJoin_round.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestJoin_round.bmp", g_visualDebug);
}

TEST(TestJoin, bevel) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestJoin_bevel.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestJoin_bevel.bmp", g_visualDebug);
}


TEST(TestJoin, bevel2) {
	std::string data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 60,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::FSNodeWriteAllData("TestJoin_bevel2.svg", data);
	doc.generateAnImage(ivec2(100, 100), "TestJoin_bevel2.bmp", g_visualDebug);
}
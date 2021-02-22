/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <esvg/esvg.hpp>
#include "main.hpp"

// ------------------------------------------------------ Miter test -----------------------------------------------------

TEST(TestJoin, miterRight1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterRight1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterRight1.bmp"), g_visualDebug);
}

TEST(TestJoin, miterRight2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterRight2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterRight2.bmp"), g_visualDebug);
}

TEST(TestJoin, miterRight3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterRight3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterRight3.bmp"), g_visualDebug);
}

TEST(TestJoin, miterRight4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterRight4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterRight4.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLeft1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLeft1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLeft1.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLeft2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLeft2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLeft2.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLeft3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLeft3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLeft3.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLeft4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLeft4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLeft4.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLimit1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='10,10 25,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLimit1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLimit1.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLimit2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='10,10 50,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLimit2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLimit2.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLimit3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='10,10 75,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLimit3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLimit3.bmp"), g_visualDebug);
}

TEST(TestJoin, miterLimit4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='10,10 90,25 10,40' stroke='green' stroke-width='20' fill='none' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterLimit4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterLimit4.bmp"), g_visualDebug);
}

TEST(TestJoin, miterCornerCasePath) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "    <path"
	                 "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
	                 "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='miter'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterCornerCasePath.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterCornerCasePath.bmp"), g_visualDebug);
}

TEST(TestJoin, miterCornerCasePathLimit) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "    <path"
	                 "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
	                 "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='miter' stroke-miterlimit='0.3'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_miterCornerCasePathLimit.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_miterCornerCasePathLimit.bmp"), g_visualDebug);
}

// ------------------------------------------------------ Round test -----------------------------------------------------

TEST(TestJoin, roundRight1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundRight1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundRight1.bmp"), g_visualDebug);
}

TEST(TestJoin, roundRight2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundRight2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundRight2.bmp"), g_visualDebug);
}

TEST(TestJoin, roundRight3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundRight3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundRight3.bmp"), g_visualDebug);
}

TEST(TestJoin, roundRight4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundRight4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundRight4.bmp"), g_visualDebug);
}

TEST(TestJoin, roundLeft1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundLeft1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundLeft1.bmp"), g_visualDebug);
}

TEST(TestJoin, roundLeft2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundLeft2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundLeft2.bmp"), g_visualDebug);
}

TEST(TestJoin, roundLeft3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundLeft3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundLeft3.bmp"), g_visualDebug);
}

TEST(TestJoin, roundLeft4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundLeft4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundLeft4.bmp"), g_visualDebug);
}

TEST(TestJoin, roundCornerCasePath) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "    <path"
	                 "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
	                 "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='round'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_roundCornerCasePath.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_roundCornerCasePath.bmp"), g_visualDebug);
}


// ------------------------------------------------------ Bevel test -----------------------------------------------------

TEST(TestJoin, bevelRight1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelRight1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelRight1.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelRight2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,80 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelRight2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelRight2.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelRight3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,80 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelRight3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelRight3.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelRight4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelRight4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelRight4.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelLeft1) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,20 50,50 80,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelLeft1.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelLeft1.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelLeft2) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='80,80 50,50 20,80' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelLeft2.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelLeft2.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelLeft3) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,80 50,50 20,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelLeft3.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelLeft3.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelLeft4) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "	<polyline points='20,20 50,50 80,20' stroke='green' stroke-width='20' fill='none' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelLeft4.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelLeft4.bmp"), g_visualDebug);
}

TEST(TestJoin, bevelCornerCasePath) {
	etk::String data("<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	                 "<svg height='100' width='100'>"
	                 "    <path"
	                 "       d='m 37.984608,9.9629707 c 6.211703,0 12.423406,0 18.635109,0 0,2.5633883 0,5.1267763 0,7.6901643 -6.211703,0 -12.423406,0 -18.635109,0 0,-2.563388 0,-5.126776 0,-7.6901643 z'\n"
	                 "       stroke='green' stroke-width='5' fill='orange' stroke-linejoin='bevel'/>"
	                 "</svg>");
	esvg::Document doc;
	doc.parse(data);
	etk::uri::writeAll(etk::Path("TestJoin_bevelCornerCasePath.svg"), data);
	doc.generateAnImage(etk::Path("TestJoin_bevelCornerCasePath.bmp"), g_visualDebug);
}

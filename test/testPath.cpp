/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <esvg/esvg.h>

TEST(TestPath, basicTest) {
	esvg::Document doc;
	/*
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg width='64' height='64'>"
	           "	<g transform='matrix(1.2,0,0,1.2,-579.7336,-567.9832)'>"
	           "		<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	           "		      style='fill:#333333;fill-rule:evenodd' />"
	           "	</g>"
	           "</svg>");
	*/
	doc.parse( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
	           "<svg width='64' height='64'>"
	           "	<g transform='matrix(1.2,0,0,1.2,-579.7336,-567.9832)'>"
	           "		<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z'"
	           "		      style='stroke:#00F;stroke-width:5;fill-rule:evenodd' />"
	           "	</g>"
	           "</svg>");
	doc.generateAnImage(128, 128);
}

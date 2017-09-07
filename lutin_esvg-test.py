#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "BINARY"

def get_sub_type():
	return "TEST"

def get_desc():
	return "eSVG test-unit"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def configure(target, my_module):
	my_module.add_src_file([
	    'test/main.cpp',
	    'test/testCircle.cpp',
	    'test/testEllipse.cpp',
	    'test/testGroup.cpp',
	    'test/testLine.cpp',
	    'test/testParsingFile.cpp',
	    'test/testPath.cpp',
	    'test/testPolygon.cpp',
	    'test/testPolyline.cpp',
	    'test/testRectangle.cpp',
	    'test/testJoin.cpp',
	    'test/testCap.cpp',
	    'test/testColor.cpp',
	    'test/testStyle.cpp',
	    'test/testGradientLinear.cpp',
	    'test/testGradientRadial.cpp'
	    ])
	my_module.add_depend([
	    'esvg',
	    'etest',
	    'test-debug'
	    ])
	return True


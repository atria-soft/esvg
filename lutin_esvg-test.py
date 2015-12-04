#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools


def get_type():
	return "BINARY"

def get_sub_type():
	return "TEST"

def get_desc():
	return "eSVG test-unit"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
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
	my_module.add_module_depend(['esvg', 'gtest', 'test-debug'])
	return my_module


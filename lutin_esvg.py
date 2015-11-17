#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "SVG image parser and generator"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def get_version():
	return [0,6,"dev"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_module_depend(['etk', 'exml'])
	my_module.add_src_file([
		'esvg/Base.cpp',
		'esvg/Circle.cpp',
		'esvg/debug.cpp',
		'esvg/Ellipse.cpp',
		'esvg/Group.cpp',
		'esvg/Line.cpp',
		'esvg/esvg.cpp',
		'esvg/Path.cpp',
		'esvg/Polygon.cpp',
		'esvg/Polyline.cpp',
		'esvg/Rectangle.cpp',
		'esvg/Renderer.cpp',
		'esvg/RenderPath.cpp',
		'esvg/Stroking.cpp',
		'esvg/Text.cpp'
		])
	
	my_module.add_header_file([
		'esvg/Base.h',
		'esvg/Circle.h',
		'esvg/Ellipse.h',
		'esvg/Group.h',
		'esvg/Line.h',
		'esvg/esvg.h',
		'esvg/Path.h',
		'esvg/Polygon.h',
		'esvg/Polyline.h',
		'esvg/Rectangle.h',
		'esvg/Renderer.h',
		'esvg/Stroking.h',
		'esvg/Text.h'
		])
	
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


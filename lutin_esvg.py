#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-svg SVG image parser and generator"

def create(target):
	my_module = module.Module(__file__, 'esvg', 'LIBRARY')
	my_module.add_module_depend(['etk', 'agg', 'exml'])
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
	# add the currrent module at the 
	return my_module


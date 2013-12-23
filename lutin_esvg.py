#!/usr/bin/python
import lutinModule as module
import lutinTools as tools

def get_desc():
	return "e-svg SVG image parser and generator"


def create(target):
	myModule = module.Module(__file__, 'esvg', 'LIBRARY')
	
	myModule.add_module_depend(['etk', 'agg', 'exml'])
	
	myModule.add_src_file([
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
		'esvg/Text.cpp'])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule








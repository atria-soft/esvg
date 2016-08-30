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
	return [0,7,1]

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
		'esvg/Text.cpp',
		'esvg/cap.cpp',
		'esvg/join.cpp',
		'esvg/spreadMethod.cpp',
		'esvg/gradientUnits.cpp',
		'esvg/Dimension.cpp',
		'esvg/render/Path.cpp',
		'esvg/render/Element.cpp',
		'esvg/render/ElementClose.cpp',
		'esvg/render/ElementStop.cpp',
		'esvg/render/ElementMoveTo.cpp',
		'esvg/render/ElementLineTo.cpp',
		'esvg/render/ElementLineToH.cpp',
		'esvg/render/ElementLineToV.cpp',
		'esvg/render/ElementCurveTo.cpp',
		'esvg/render/ElementSmoothCurveTo.cpp',
		'esvg/render/ElementBezierCurveTo.cpp',
		'esvg/render/ElementBezierSmoothCurveTo.cpp',
		'esvg/render/ElementElliptic.cpp',
		'esvg/render/Point.cpp',
		'esvg/render/PointList.cpp',
		'esvg/render/Scanline.cpp',
		'esvg/render/Segment.cpp',
		'esvg/render/SegmentList.cpp',
		'esvg/render/Weight.cpp',
		'esvg/render/DynamicColor.cpp',
		'esvg/LinearGradient.cpp',
		'esvg/RadialGradient.cpp'
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
		'esvg/Text.h',
		'esvg/cap.h',
		'esvg/join.h',
		'esvg/spreadMethod.h',
		'esvg/gradientUnits.h',
		'esvg/Dimension.h',
		'esvg/render/Element.h',
		'esvg/render/ElementStop.h',
		'esvg/render/ElementClose.h',
		'esvg/render/ElementMoveTo.h',
		'esvg/render/ElementLineTo.h',
		'esvg/render/ElementLineToH.h',
		'esvg/render/ElementLineToV.h',
		'esvg/render/ElementCurveTo.h',
		'esvg/render/ElementSmoothCurveTo.h',
		'esvg/render/ElementBezierCurveTo.h',
		'esvg/render/ElementBezierSmoothCurveTo.h',
		'esvg/render/ElementElliptic.h',
		'esvg/render/Path.h',
		'esvg/render/Scanline.h',
		'esvg/render/Point.h',
		'esvg/render/PointList.h',
		'esvg/render/Segment.h',
		'esvg/render/SegmentList.h',
		'esvg/render/Weight.h',
		'esvg/render/DynamicColor.h',
		'esvg/LinearGradient.h',
		'esvg/RadialGradient.h'
		])
	
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


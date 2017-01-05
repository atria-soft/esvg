#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "SVG image parser and generator"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def get_version():
	return "version.txt"

def configure(target, my_module):
	my_module.add_depend(['etk', 'exml'])
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
	    'esvg/Base.hpp',
	    'esvg/Circle.hpp',
	    'esvg/Ellipse.hpp',
	    'esvg/Group.hpp',
	    'esvg/Line.hpp',
	    'esvg/esvg.hpp',
	    'esvg/Path.hpp',
	    'esvg/Polygon.hpp',
	    'esvg/Polyline.hpp',
	    'esvg/Rectangle.hpp',
	    'esvg/Renderer.hpp',
	    'esvg/Text.hpp',
	    'esvg/cap.hpp',
	    'esvg/join.hpp',
	    'esvg/spreadMethod.hpp',
	    'esvg/gradientUnits.hpp',
	    'esvg/Dimension.hpp',
	    'esvg/render/Element.hpp',
	    'esvg/render/ElementStop.hpp',
	    'esvg/render/ElementClose.hpp',
	    'esvg/render/ElementMoveTo.hpp',
	    'esvg/render/ElementLineTo.hpp',
	    'esvg/render/ElementLineToH.hpp',
	    'esvg/render/ElementLineToV.hpp',
	    'esvg/render/ElementCurveTo.hpp',
	    'esvg/render/ElementSmoothCurveTo.hpp',
	    'esvg/render/ElementBezierCurveTo.hpp',
	    'esvg/render/ElementBezierSmoothCurveTo.hpp',
	    'esvg/render/ElementElliptic.hpp',
	    'esvg/render/Path.hpp',
	    'esvg/render/Scanline.hpp',
	    'esvg/render/Point.hpp',
	    'esvg/render/PointList.hpp',
	    'esvg/render/Segment.hpp',
	    'esvg/render/SegmentList.hpp',
	    'esvg/render/Weight.hpp',
	    'esvg/render/DynamicColor.hpp',
	    'esvg/LinearGradient.hpp',
	    'esvg/RadialGradient.hpp'
	    ])
	
	my_module.add_path(".")
	return True


#!/usr/bin/python
import realog.debug as debug
import lutin.tools as tools
import realog.debug as debug
import lutin.image as image
import os
import lutin.multiprocess as lutinMultiprocess


def get_type():
	return "LIBRARY_DYNAMIC"

def get_desc():
	return "Ewol Tool Kit"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "org"

def get_compagny_name():
	return "atria-soft"

#def get_maintainer():
#	return "authors.txt"

#def get_version():
#	return "version.txt"

def configure(target, my_module):

	my_module.add_src_file([
	    'src/module-info.java',
	    'src/org/atriasoft/esvg/LinearGradient.java',
	    'src/org/atriasoft/esvg/Circle.java',
	    'src/org/atriasoft/esvg/Group.java',
	    'src/org/atriasoft/esvg/Base.java',
	    'src/org/atriasoft/esvg/Text.java',
	    'src/org/atriasoft/esvg/RadialGradient.java',
	    'src/org/atriasoft/esvg/internal/Log.java',
	    'src/org/atriasoft/esvg/font/Kerning.java',
	    'src/org/atriasoft/esvg/font/Glyph.java',
	    'src/org/atriasoft/esvg/Renderer.java',
	    'src/org/atriasoft/esvg/EsvgFont.java',
	    'src/org/atriasoft/esvg/FontCache.java',
	    'src/org/atriasoft/esvg/Ellipse.java',
	    'src/org/atriasoft/esvg/Esvg.java',
	    'src/org/atriasoft/esvg/render/ElementLineToH.java',
	    'src/org/atriasoft/esvg/render/DynamicColor.java',
	    'src/org/atriasoft/esvg/render/Point.java',
	    'src/org/atriasoft/esvg/render/Scanline.java',
	    'src/org/atriasoft/esvg/render/PathType.java',
	    'src/org/atriasoft/esvg/render/ElementLineToV.java',
	    'src/org/atriasoft/esvg/render/PointList.java',
	    'src/org/atriasoft/esvg/render/ElementMoveTo.java',
	    'src/org/atriasoft/esvg/render/SegmentList.java',
	    'src/org/atriasoft/esvg/render/Segment.java',
	    'src/org/atriasoft/esvg/render/ElementElliptic.java',
	    'src/org/atriasoft/esvg/render/ElementStop.java',
	    'src/org/atriasoft/esvg/render/Weight.java',
	    'src/org/atriasoft/esvg/render/ElementBezierSmoothCurveTo.java',
	    'src/org/atriasoft/esvg/render/DynamicColorSpecial.java',
	    'src/org/atriasoft/esvg/render/PathModel.java',
	    'src/org/atriasoft/esvg/render/ElementBezierCurveTo.java',
	    'src/org/atriasoft/esvg/render/RenderingConfig.java',
	    'src/org/atriasoft/esvg/render/ElementLineTo.java',
	    'src/org/atriasoft/esvg/render/PointType.java',
	    'src/org/atriasoft/esvg/render/ElementCurveTo.java',
	    'src/org/atriasoft/esvg/render/ElementClose.java',
	    'src/org/atriasoft/esvg/render/DynamicColorUni.java',
	    'src/org/atriasoft/esvg/render/Element.java',
	    'src/org/atriasoft/esvg/render/ElementSmoothCurveTo.java',
	    'src/org/atriasoft/esvg/PaintState.java',
	    'src/org/atriasoft/esvg/PaintMode.java',
	    'src/org/atriasoft/esvg/CapMode.java',
	    'src/org/atriasoft/esvg/Path.java',
	    'src/org/atriasoft/esvg/Polygon.java',
	    'src/org/atriasoft/esvg/Rectangle.java',
	    'src/org/atriasoft/esvg/JoinMode.java',
	    'src/org/atriasoft/esvg/SpreadMethod.java',
	    'src/org/atriasoft/esvg/EsvgDocument.java',
	    'src/org/atriasoft/esvg/Line.java',
	    'src/org/atriasoft/esvg/GraphicContext.java',
	    'src/org/atriasoft/esvg/GradientUnits.java',
	    'src/org/atriasoft/esvg/Polyline.java',
	    ])
	my_module.add_path('src/', type='java')
	
	my_module.add_depend([
	    'org-atriasoft-exml',
	    'org-atriasoft-pngencoder',
	    'org-atriasoft-egami',
	    ])
	
	#my_module.add_path([
	#    'lib/spotbugs-annotations-4.2.2.jar'
	#    ],
	#    type='java',
	#    export=True
	#);
	my_module.add_flag('java', "RELEASE_15_PREVIEW");
	
	return True


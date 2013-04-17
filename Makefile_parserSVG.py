#!/usr/bin/python
import module
import buildTools

myModule = module.module(__file__, 'parsersvg', 'LIBRARY')

myModule.AddModuleDepend(['etk', 'agg', 'tinyxml'])

myModule.AddSrcFile([
	'parserSVG/Base.cpp',
	'parserSVG/Circle.cpp',
	'parserSVG/Debug.cpp',
	'parserSVG/Ellipse.cpp',
	'parserSVG/Group.cpp',
	'parserSVG/Line.cpp',
	'parserSVG/parserSVG.cpp',
	'parserSVG/Path.cpp',
	'parserSVG/Polygon.cpp',
	'parserSVG/Polyline.cpp',
	'parserSVG/Rectangle.cpp',
	'parserSVG/Renderer.cpp',
	'parserSVG/Stroking.cpp',
	'parserSVG/Text.cpp'])

myModule.CompileFlags_CC([
	'-DPARSER_SVG_VERSION_TAG_NAME="todo-Tag"'])

myModule.AddExportPath(buildTools.GetCurrentPath(__file__))

# add the currrent module at the 
module.AddModule(myModule)








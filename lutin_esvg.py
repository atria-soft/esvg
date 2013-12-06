#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	myModule = lutinModule.module(__file__, 'esvg', 'LIBRARY')
	# enable doculentation :
	myModule.doc_enable()
	myModule.documentation.set_website("http://HeeroYui.github.io/esvg/doc/doc/")
	myModule.documentation.set_path(lutinTools.GetCurrentPath(__file__) + "/esvg/")
	myModule.documentation.set_external_link(['etk', 'agg', 'exml'])
	
	myModule.AddModuleDepend(['etk', 'agg', 'exml'])
	
	myModule.AddSrcFile([
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
	
	myModule.AddExportPath(lutinTools.GetCurrentPath(__file__))
	
	# add the currrent module at the 
	return myModule








#!/usr/bin/python
import monkModule as module
import monkTools as tools

def get_desc():
	return "e-svg SVG image parser and generator"


def create():
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'esvg', 'LIBRARY')
	# enable doculentation :
	myModule.set_website("http://heeroyui.github.io/esvg/")
	myModule.set_website_sources("http://github.com/heeroyui/esvg/")
	myModule.set_path(tools.get_current_path(__file__) + "/esvg/")
	# add the currrent module at the 
	return myModule

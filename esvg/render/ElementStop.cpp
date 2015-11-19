/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Element.h>
#include <esvg/debug.h>



esvg::render::ElementStop::ElementStop(bool _relative):
  Element(esvg::render::path_stop, _relative) {
	
}

std::string esvg::render::ElementStop::display() const {
	return "";
}



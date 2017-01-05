/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementStop::ElementStop():
  Element(esvg::render::path_stop) {
	
}

std::string esvg::render::ElementStop::display() const {
	return "";
}



/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

esvg::render::ElementClose::ElementClose(bool _relative):
  Element(esvg::render::path_close, _relative) {
	
}

etk::String esvg::render::ElementClose::display() const {
	return "";
}



/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/render/DynamicColor.h>

esvg::render::DynamicColorLinear::DynamicColorLinear(const std::string& _link, const mat2& _mtx, const vec2 _objectSize, const vec2 _objectPos)
   {
	
}


etk::Color<float,4> esvg::render::DynamicColorLinear::getColor(const ivec2& _pos) {
	return etk::color::purple;
}


std::shared_ptr<esvg::render::DynamicColor> esvg::render::createColor(std::pair<etk::Color<float,4>, std::string> _color, const mat2& _mtx, const vec2 _size) {
	// Check if need to create a color:
	if (    _color.first.a() == 0x00
	     && _color.second == "") {
	     return nullptr;
	}
	if (_color.second != "") {
		return std::make_shared<esvg::render::DynamicColorLinear>(_color.second, _mtx, _size);
	}
	return std::make_shared<esvg::render::DynamicColorUni>(_color.first);
}

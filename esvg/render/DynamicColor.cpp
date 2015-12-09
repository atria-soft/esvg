/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/render/DynamicColor.h>
#include <esvg/LinearGradient.h>
#include <esvg/esvg.h>

esvg::render::DynamicColorLinear::DynamicColorLinear(const std::string& _link, const mat2& _mtx, const vec2 _size) :
  m_colorName(_link),
  m_matrix(_mtx),
  m_size(_size) {
	
}


etk::Color<float,4> esvg::render::DynamicColorLinear::getColor(const ivec2& _pos) {
	return etk::color::purple;
}

void esvg::render::DynamicColorLinear::generate(esvg::Document* _document) {
	if (_document == nullptr) {
		ESVG_ERROR("Get nullptr input for document");
		return;
	}
	std::shared_ptr<esvg::Base> base = _document->getReference(m_colorName);
	if (base == nullptr) {
		ESVG_ERROR("Can not get base : '" << m_colorName << "'");
		return;
	}
	std::shared_ptr<esvg::LinearGradient> gradient = std::dynamic_pointer_cast<esvg::LinearGradient>(base);
	if (gradient == nullptr) {
		ESVG_ERROR("Can not cast in a linear gradient: '" << m_colorName << "' ==> wrong type");
		return;
	}
	ESVG_INFO("get for color linear:");
	gradient->display(2);
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

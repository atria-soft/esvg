/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Scanline.h>
#include <esvg/debug.h>

#undef __class__
#define __class__	"rerder::Scanline"

esvg::render::Scanline::Scanline(size_t _size) {
	float tmp(0);
	m_data.resize(_size, tmp);
}

size_t esvg::render::Scanline::size() const {
	return m_data.size();
}

void esvg::render::Scanline::clear(float _fill) {
	for (auto &it : m_data) {
		it = _fill;
	}
}

float esvg::render::Scanline::get(int32_t _pos) const {
	if(    _pos>=0
	    && _pos<m_data.size()) {
		return m_data[_pos];
	}
	return 0;
}

void esvg::render::Scanline::set(int32_t _pos, float _newColor) {
	if(    _pos>=0
	    && _pos<m_data.size()) {
		m_data[_pos] = _newColor;
	}
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Scanline.hpp>
#include <esvg/debug.hpp>

esvg::render::Scanline::Scanline(size_t _size) {
	this.data.resize(_size, 0.0f);
}

size_t esvg::render::Scanline::size() const {
	return this.data.size();
}

void esvg::render::Scanline::clear(float _fill) {
	for (auto &it : this.data) {
		it = _fill;
	}
}

float esvg::render::Scanline::get(int _pos) const {
	if(    _pos >= 0
	    && size_t(_pos) < this.data.size()) {
		return this.data[_pos];
	}
	return 0;
}

void esvg::render::Scanline::set(int _pos, float _newColor) {
	if(    _pos >= 0
	    && size_t(_pos) < this.data.size()) {
		this.data[_pos] = _newColor;
	}
}


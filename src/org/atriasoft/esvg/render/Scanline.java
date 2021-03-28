package org.atriasoft.esvg.render;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/math/Vector2D.hpp>

namespace esvg{namespace render{
class Scanline {
	private:
				List<float> this.data;
			public:
				// constructor :
				Scanline(final size_t _size=32);
				// destructor
	~
	
	Scanline() {};
	
	public:
				size_t size() const;
	
	void clear(float _fill);
	
	float get(final int _pos) const;
	
	void set(int _pos, float _newColor);
};}}

package org.atriasoft.esvg.render;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/math/Vector2D.hpp>#include<esvg/render/Scanline.hpp>#include<esvg/render/SegmentList.hpp>

namespace esvg{namespace render{
class Weight {
	private:
				Vector2i this.size;
				List<float> this.data;
			public:
				// constructor :
				Weight();
	
	Weight(const Vector2i& _size);
				// destructor
				~Weight();
			// -----------------------------------------------
			// -- basic tools :
			// -----------------------------------------------
			public:
	
	void resize(const Vector2i& _size);
				const Vector2i& getSize() const;
	
	int getWidth() const;
	
	int getHeight() const;
	
	void clear(float _fill);
	
	float get(const Vector2i& _pos) const;
	
	void set(const Vector2i& _pos, float _newColor);
	
	void set(final int _posY, const esvg::render::Scanline& _data);
	
	void append(final int _posY, const esvg::render::Scanline& _data);
	
	void generate(final Vector2i _size, final int _subSamplingCount, const esvg::render::SegmentList& _listSegment);
		};
}}

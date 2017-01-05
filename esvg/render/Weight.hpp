/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <esvg/render/Scanline.hpp>
#include <esvg/render/SegmentList.hpp>

namespace esvg {
	namespace render {
		class Weight {
			private:
				ivec2 m_size;
				std::vector<float> m_data;
			public:
				// constructor :
				Weight();
				Weight(const ivec2& _size);
				// destructor
				~Weight();
			// -----------------------------------------------
			// -- basic tools :
			// -----------------------------------------------
			public:
				void resize(const ivec2& _size);
				const ivec2& getSize() const;
				int32_t getWidth() const;
				int32_t getHeight() const;
				void clear(float _fill);
				float get(const ivec2& _pos) const;
				void set(const ivec2& _pos, float _newColor);
				void set(int32_t _posY, const esvg::render::Scanline& _data);
				void append(int32_t _posY, const esvg::render::Scanline& _data);
				void generate(ivec2 _size, int32_t _subSamplingCount, const esvg::render::SegmentList& _listSegment);
		};
	}
}


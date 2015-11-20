/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDERER_H__
#define __ESVG_RENDERER_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>
#include <esvg/render/Weight.h>

namespace esvg {
	class Renderer {
		#ifdef DEBUG
		private:
			bool m_visualDebug;
			int32_t m_factor;
		#endif
		public:
			Renderer(const ivec2& _size, bool _visualDebug=false);
			~Renderer();
		protected:
			ivec2 m_size;
		public:
			void setSize(const ivec2& _size);
			const ivec2& getSize() const;
		protected:
			std::vector<uint8_t> m_buffer;
		public:
			uint8_t* getDataPointer();
			uint32_t getDataSize() const;
		protected:
			int32_t m_interpolationRecurtionMax;
		public:
			void setInterpolationRecurtionMax(int32_t _value);
			int32_t getInterpolationRecurtionMax() const;
		protected:
			float m_interpolationThreshold;
		public:
			void setInterpolationThreshold(float _value);
			float getInterpolationThreshold() const;
		protected:
			int32_t m_nbSubScanLine;
		public:
			void setNumberSubScanLine(int32_t _value);
			int32_t getNumberSubScanLine() const;
		public:
			void writePpm(std::string fileName);
		public:
			void print(const esvg::render::Weight& _weightFill,
			           const etk::Color<uint8_t,4>& _colorFill,
			           const esvg::render::Weight& _weightStroke,
			           const etk::Color<uint8_t,4>& _colorStroke);
			#ifdef DEBUG
			void addDebugSegment(const esvg::render::SegmentList& _listSegment);
			#endif
	};
};

#endif

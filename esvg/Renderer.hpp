/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/Color.hpp>
#include <esvg/render/Weight.hpp>
#include <esvg/render/DynamicColor.hpp>

namespace esvg {
	class Document;
	class Renderer {
		#ifdef DEBUG
		private:
			bool m_visualDebug;
			int32_t m_factor;
		#endif
		public:
			Renderer(const ivec2& _size, esvg::Document* _document, bool _visualDebug=false);
			~Renderer();
		protected:
			ivec2 m_size;
		public:
			void setSize(const ivec2& _size);
			const ivec2& getSize() const;
		protected:
			std::vector<etk::Color<float,4>> m_buffer;
		public:
			std::vector<etk::Color<float,4>> getData();
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
			void writePPM(const std::string& _fileName);
			void writeBMP(const std::string& _fileName);
		protected:
			etk::Color<float,4> mergeColor(etk::Color<float,4> _base, etk::Color<float,4> _integration);
		public:
			void print(const esvg::render::Weight& _weightFill,
			           ememory::SharedPtr<esvg::render::DynamicColor>& _colorFill,
			           const esvg::render::Weight& _weightStroke,
			           ememory::SharedPtr<esvg::render::DynamicColor>& _colorStroke,
			           float _opacity);
			#ifdef DEBUG
			void addDebugSegment(const esvg::render::SegmentList& _listSegment);
			void addDebug(const std::vector<std::pair<vec2,vec2>>& _info);
			#endif
		protected:
			esvg::Document* m_document;
		public:
			esvg::Document* getMainDocument() {
				return m_document;
			}
	};
}


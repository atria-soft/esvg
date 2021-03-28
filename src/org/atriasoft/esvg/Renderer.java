package org.atriasoft.esvg;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/math/Vector2D.hpp>#include<etk/Color.hpp>#include<esvg/render/Weight.hpp>#include<esvg/render/DynamicColor.hpp>#include<etk/uri/uri.hpp>

namespace esvg{
class Document;
class Renderer {
		#ifdef DEBUG
		
		private:
			boolean this.visualDebug;
			int this.factor;
		#endif
		public:
			Renderer(const Vector2i& _size, esvg::Document* _document, boolean _visualDebug=false);
			~Renderer();
		protected:
			Vector2i this.size;
		public:
		
		void setSize(const Vector2i& _size);
			const Vector2i& getSize() const;
		protected:
			List<etk::Color<float,4>> this.buffer;
		public:
			List<etk::Color<float,4>> getData();
		protected:
			int this.interpolationRecurtionMax;
		public:
		
		void setInterpolationRecurtionMax(int _value);
		
		int getInterpolationRecurtionMax() const;
		protected:
			float this.interpolationThreshold;
		public:
		
		void setInterpolationThreshold(float _value);
		
		float getInterpolationThreshold() const;
		protected:
			int this.nbSubScanLine;
		public:
		
		void setNumberSubScanLine(int _value);
		
		int getNumberSubScanLine() const;
		public:
		
		void writePPM(const etk::Uri& _uri);
		
		void writeBMP(const etk::Uri& _uri);
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
		
		void addDebug(const List<Pair<Vector2f,Vector2f>>& _info);
			#endif
		protected:
			esvg::Document* this.document;
		public:
			esvg::Document*
		
		getMainDocument() {
				return this.document;
			}
	};
}

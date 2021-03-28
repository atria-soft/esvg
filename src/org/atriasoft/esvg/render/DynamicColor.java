package org.atriasoft.esvg.render;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<ememory/memory.hpp>#include<etk/types.hpp>#include<etk/Pair.hpp>#include<etk/Color.hpp>#include<etk/math/Vector2D.hpp>#include<etk/math/Matrix2x3.hpp>#include<esvg/gradientUnits.hpp>#include<esvg/spreadMethod.hpp>

namespace esvg{
class Document;
namespace render
{
		class DynamicColor {
			public:
				DynamicColor() {
					// nothing to do ...
				}
				virtual ~DynamicColor() {};
				virtual etk::Color<float,4> getColor(const Vector2i& _pos) const = 0;
				virtual void generate(esvg::Document* _document) = 0;
				virtual void setViewPort(const Pair<Vector2f, Vector2f>& _viewPort) = 0;
		};
		class DynamicColorUni  extends  esvg::render::DynamicColor {
			public:
				etk::Color<float,4> this.color;
			public:
				DynamicColorUni(const etk::Color<float,4>& _color) :
				  this.color(_color) {
					
				}
				virtual etk::Color<float,4> getColor(const Vector2i& _pos) const {
					return this.color;
				}
				virtual void generate(esvg::Document* _document) {
					// nothing to do ...
				}
				virtual void setViewPort(const Pair<Vector2f, Vector2f>& _viewPort) {
					// nothing to do ...
				};
		};
		class DynamicColorSpecial  extends  esvg::render::DynamicColor {
			public:
				boolean this.linear;
				esvg::spreadMethod this.spread;
				esvg::gradientUnits this.unit;
				etk::String this.colorName;
				mat2x3 this.matrix;
				Pair<Vector2f, Vector2f> this.viewPort;
				Vector2f this.pos1; // in radius ==> center
				Vector2f this.pos2; // in radius ==> radius end position
				Vector2f this.focal; // Specific radius
				Vector2f this.axeX;
				Vector2f this.axeY;
				Vector2f this.baseSize;
				float this.focalLength;
				boolean this.clipOut;
				boolean this.centerIsFocal;
				List<Pair<float, etk::Color<float,4>>> this.data;
			public:
				DynamicColorSpecial(const etk::String& _link, const mat2x3& _mtx);
				virtual etk::Color<float,4> getColor(const Vector2i& _pos) const;
			private:
				etk::Color<float,4> getColorLinear(const Vector2i& _pos) const;
				etk::Color<float,4> getColorRadial(const Vector2i& _pos) const;
			public:
				virtual void generate(esvg::Document* _document);
				virtual void setViewPort(const Pair<Vector2f, Vector2f>& _viewPort);
		};
		
		ememory::SharedPtr<DynamicColor> createColor(Pair<etk::Color<float,4>, etk::String> _color, const mat2x3& _mtx);
	}
}

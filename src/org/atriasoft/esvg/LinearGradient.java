package org.atriasoft.esvg;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<esvg/Base.hpp>#include<esvg/gradientUnits.hpp>#include<esvg/spreadMethod.hpp>

namespace esvg{
class Document;
class LinearGradient extends esvg::Base
{
		private:
			esvg::Dimension this.pos1; //!< gradient position x1 y1
			esvg::Dimension this.pos2; //!< gradient position x2 y2
		public:
			enum gradientUnits this.unit;
			enum spreadMethod this.spread;
		private:
			etk::String this.href; //!< in case of using a single gradient in multiple gradient, the gradient is store in an other element...
			List<Pair<float, etk::Color<float,4>>> this.data; //!< incompatible with href
		public:
			LinearGradient(PaintState _parentPaintState);
			~LinearGradient();
			virtual boolean parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax);
			virtual void display(int _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level);
		public:
			const esvg::Dimension& getPosition1();
			const esvg::Dimension& getPosition2();
			const List<Pair<float, etk::Color<float,4>>>& getColors(esvg::Document* _document);
	};
}

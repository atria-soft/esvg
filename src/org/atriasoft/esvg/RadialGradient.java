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
class RadialGradient extends esvg::Base
{
		private:
			esvg::Dimension this.center; //!< gradient position cx cy
			esvg::Dimension1D this.radius; //!< Radius of the gradient
			esvg::Dimension this.focal; //!< gradient Focal fx fy
		public:
			enum gradientUnits this.unit;
			enum spreadMethod this.spread;
		private:
			etk::String this.href; //!< in case of using a single gradient in multiple gradient, the gradient is store in an other element...
			List<Pair<float, etk::Color<float,4>>> this.data; //!< incompatible with href
		public:
			RadialGradient(PaintState _parentPaintState);
			~RadialGradient();
			virtual boolean parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax);
			virtual void display(int _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level);
		public:
			const esvg::Dimension& getCenter();
			const esvg::Dimension& getFocal();
			const esvg::Dimension1D& getRadius();
			const List<Pair<float, etk::Color<float,4>>>& getColors(esvg::Document* _document);
	};
}

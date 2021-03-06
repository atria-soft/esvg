/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>
#include <esvg/gradientUnits.hpp>
#include <esvg/spreadMethod.hpp>

namespace esvg {
	class Document;
	class LinearGradient : public esvg::Base {
		private:
			esvg::Dimension m_pos1; //!< gradient position x1 y1
			esvg::Dimension m_pos2; //!< gradient position x2 y2
		public:
			enum gradientUnits m_unit;
			enum spreadMethod m_spread;
		private:
			etk::String m_href; //!< in case of using a single gradient in multiple gradient, the gradient is store in an other element...
			etk::Vector<etk::Pair<float, etk::Color<float,4>>> m_data; //!< incompatible with href
		public:
			LinearGradient(PaintState _parentPaintState);
			~LinearGradient();
			virtual bool parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level);
		public:
			const esvg::Dimension& getPosition1();
			const esvg::Dimension& getPosition2();
			const etk::Vector<etk::Pair<float, etk::Color<float,4>>>& getColors(esvg::Document* _document);
	};
}


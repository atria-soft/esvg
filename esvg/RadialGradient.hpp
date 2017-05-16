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
	class RadialGradient : public esvg::Base {
		private:
			esvg::Dimension m_center; //!< gradient position cx cy
			esvg::Dimension1D m_radius; //!< Radius of the gradient
			esvg::Dimension m_focal; //!< gradient Focal fx fy
		public:
			enum gradientUnits m_unit;
			enum spreadMethod m_spread;
		private:
			std::string m_href; //!< in case of using a single gradient in multiple gradient, the gradient is store in an other element...
			std::vector<std::pair<float, etk::Color<float,4>>> m_data; //!< incompatible with href
		public:
			RadialGradient(PaintState _parentPaintState);
			~RadialGradient();
			virtual bool parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level);
		public:
			const esvg::Dimension& getCenter();
			const esvg::Dimension& getFocal();
			const esvg::Dimension1D& getRadius();
			const std::vector<std::pair<float, etk::Color<float,4>>>& getColors(esvg::Document* _document);
	};
}


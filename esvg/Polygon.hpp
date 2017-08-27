/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.hpp>
#include <etk/Vector.hpp>

namespace esvg {
	/*
	enum polygonMode {
		polygoneModeNonZero,
		polygoneModeEvenOdd
	};
	*/
	class Polygon : public esvg::Base {
		private:
			etk::Vector<vec2 > m_listPoint; //!< list of all point of the polygone
			//enum esvg::polygonMode m_diplayMode; //!< polygone specific display mode
		public:
			Polygon(PaintState parentPaintState);
			~Polygon();
			bool parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax) override;
			void display(int32_t _spacing) override;
			void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) override;
			void drawShapePoints(etk::Vector<etk::Vector<vec2>>& _out,
			                     int32_t _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int32_t _level=1) override;
		private:
			esvg::render::Path createPath();
	};
}


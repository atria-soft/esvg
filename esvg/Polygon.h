/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_POLYGON_H__
#define __ESVG_POLYGON_H__

#include <esvg/Base.h>
#include <vector>

namespace esvg {
	/*
	enum polygonMode {
		polygoneModeNonZero,
		polygoneModeEvenOdd
	};
	*/
	class Polygon : public esvg::Base {
		private:
			std::vector<vec2 > m_listPoint; //!< list of all point of the polygone
			//enum esvg::polygonMode m_diplayMode; //!< polygone specific display mode
		public:
			Polygon(PaintState parentPaintState);
			~Polygon();
			virtual bool parseXML(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
};

#endif


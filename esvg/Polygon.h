/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
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
			std::vector<etk::Vector2D<float> > m_listPoint; //!< list of all point of the polygone
			//enum esvg::polygonMode m_diplayMode; //!< polygone specific display mode
		public:
			Polygon(PaintState parentPaintState);
			~Polygon(void);
			virtual bool parse(exml::Element * _element, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax);
			virtual void display(int32_t spacing);
			virtual void aggDraw(esvg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


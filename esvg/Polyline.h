/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_POLYLINE_H__
#define __ESVG_POLYLINE_H__

#include <esvg/Base.h>
#include <vector>

namespace esvg {
	class Polyline : public esvg::Base {
		private:
			std::vector<etk::Vector2D<float> > m_listPoint;    //!< list of all point of the polyline
		public:
			Polyline(PaintState _parentPaintState);
			~Polyline();
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_POLYLINE_H__
#define __ESVG_POLYLINE_H__

#include <esvg/Base.h>
#include <etk/Vector.h>

namespace esvg
{
	class Polyline : public esvg::Base
	{
		private:
			etk::Vector<etk::Vector2D<float> > m_listPoint;    //!< list of all point of the polyline
		public:
			Polyline(PaintState _parentPaintState);
			~Polyline(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t _spacing);
			virtual void AggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


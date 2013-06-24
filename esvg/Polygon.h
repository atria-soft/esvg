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
#include <etk/Vector.h>

namespace esvg
{
	typedef enum {
		POLYGONE_MODE__NON_ZERO,
		POLYGONE_MODE__EVEN_ODD,
	} PolygonMode_te;
	class Polygon : public esvg::Base
	{
		private:
			etk::Vector<etk::Vector2D<float> > m_listPoint;    //!< list of all point of the polygone
			PolygonMode_te                    m_diplayMode;   //!< polygone specific display mode
		public:
			Polygon(PaintState parentPaintState);
			~Polygon(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(esvg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


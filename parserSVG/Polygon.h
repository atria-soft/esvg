/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_POLYGON_H__
#define __SVG_POLYGON_H__

#include <parserSVG/Base.h>
#include <etk/Vector.h>

namespace svg
{
	typedef enum {
		POLYGONE_MODE__NON_ZERO,
		POLYGONE_MODE__EVEN_ODD,
	} PolygonMode_te;
	class Polygon : public svg::Base
	{
		private:
			etk::Vector<etk::Vector2D<float> > m_listPoint;    //!< list of all point of the polygone
			PolygonMode_te                    m_diplayMode;   //!< polygone specific display mode
		public:
			Polygon(PaintState parentPaintState);
			~Polygon(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


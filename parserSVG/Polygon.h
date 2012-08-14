/**
 *******************************************************************************
 * @file parserSVG/Polygon.h
 * @brief basic poligon parsing (Header)
 * @author Edouard DUPIN
 * @date 20/03/2012
 * @par Project
 * parserSVG
 *
 * @par Copyright
 * Copyright 2011 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
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
			etk::Vector<Vector2D<float> > m_listPoint;    //!< list of all point of the polygone
			PolygonMode_te                    m_diplayMode;   //!< polygone specific display mode
		public:
			Polygon(PaintState parentPaintState);
			~Polygon(void);
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


/**
 *******************************************************************************
 * @file parserSVG/Circle.h
 * @brief basic circle parsing (Header)
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

#ifndef __SVG_CIRCLE_H__
#define __SVG_CIRCLE_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Circle : public svg::Base
	{
		private:
			Vector2D<float> m_position;        //!< Position of the Circle
			float           m_radius;          //!< Radius of the Circle
		public:
			Circle(PaintState parentPaintState);
			~Circle(void);
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


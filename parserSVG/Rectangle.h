/**
 *******************************************************************************
 * @file parserSVG/Rectangle.h
 * @brief basic rectangle parsing (Header)
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

#ifndef __SVG_RECTANGLE_H__
#define __SVG_RECTANGLE_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Rectangle : public svg::Base
	{
		private:
			etk::Vector2D<float> m_position;        //!< position of the rectangle
			etk::Vector2D<float> m_size;            //!< size of the rectangle
			etk::Vector2D<float> m_roundedCorner;   //!< property of the rounded corner
		public:
			Rectangle(PaintState parentPaintState);
			~Rectangle(void);
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


/**
 *******************************************************************************
 * @file parserSVG/Text.h
 * @brief Basic Text parsing (Header)
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

#ifndef __SVG_TEXT_H__
#define __SVG_TEXT_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Text : public svg::Base
	{
		private:
			
		public:
			Text(PaintState parentPaintState);
			~Text(void);
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
	};
};

#endif


/**
 *******************************************************************************
 * @file parserSVG/Group.h
 * @brief basic group parsing (Header)
 * @author Edouard DUPIN
 * @date 21/03/2012
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

#ifndef __SVG_GROUP_H__
#define __SVG_GROUP_H__

#include <parserSVG/Base.h>
#include <etk/VectorType.h>

namespace svg
{
	class Group : public svg::Base
	{
		private:
			etk::VectorType<svg::Base *> m_subElementList;  //!< group sub elements ...
		public:
			Group(PaintState parentPaintState);
			~Group(void);
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


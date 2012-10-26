/**
 *******************************************************************************
 * @file parserSVG/Text.cpp
 * @brief Basic Text parsing (Sources)
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

#include <parserSVG/Debug.h>
#include <parserSVG/Text.h>

svg::Text::Text(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	
}

svg::Text::~Text(void)
{
	
}

bool svg::Text::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax)
{
	sizeMax.x = 0;
	sizeMax.y = 0;
	SVG_ERROR("NOT IMPLEMENTED");
	return false;
}

void svg::Text::Display(int32_t spacing)
{
	SVG_DEBUG(SpacingDist(spacing) << "Text");
}



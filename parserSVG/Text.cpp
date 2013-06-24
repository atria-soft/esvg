/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Text.h>

svg::Text::Text(PaintState _parentPaintState) : svg::Base(_parentPaintState)
{
	
}

svg::Text::~Text(void)
{
	
}

bool svg::Text::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	_sizeMax.setValue(0,0);
	SVG_ERROR("NOT IMPLEMENTED");
	return false;
}

void svg::Text::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Text");
}



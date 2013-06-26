/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/Debug.h>
#include <esvg/Text.h>

#undef __class__
#define __class__	"Text"

esvg::Text::Text(PaintState _parentPaintState) : esvg::Base(_parentPaintState)
{
	
}

esvg::Text::~Text(void)
{
	
}

bool esvg::Text::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	_sizeMax.setValue(0,0);
	SVG_ERROR("NOT IMPLEMENTED");
	return false;
}

void esvg::Text::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Text");
}



/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Text.h>

#undef __class__
#define __class__	"Text"

esvg::Text::Text(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Text::~Text() {
	
}

bool esvg::Text::parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	_sizeMax.setValue(0,0);
	SVG_ERROR("NOT IMPLEMENTED");
	return false;
}

void esvg::Text::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Text");
}



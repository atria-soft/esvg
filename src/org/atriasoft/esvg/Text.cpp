/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Text.hpp>

esvg::Text::Text(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Text::~Text() {
	
}

boolean esvg::Text::parse(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	_sizeMax.setValue(0,0);
	Log.error("NOT IMPLEMENTED");
	return false;
}

void esvg::Text::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Text");
}



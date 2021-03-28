package org.atriasoft.esvg;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

class Text extends Base {
	public Text(final PaintState _parentPaintState) {
		super(_parentPaintState);
	}
	
	@Override
		public boolean parse(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax)
		_sizeMax.setValue(0,0);
		Log.error("NOT IMPLEMENTED");
		return false;
}
	
	@Override
	public void display(final int _spacing) {
		Log.debug(spacingDist(_spacing) << "Text");
	}
}

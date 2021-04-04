package org.atriasoft.esvg;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.exml.model.XmlElement;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Text extends Base {
	public Text(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	@Override
	public void display(final int spacing) {
		Log.debug(spacingDist(spacing) + "Text");
	}
	
	@Override
	public boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		sizeMax.value = Vector2f.ZERO;
		Log.error("NOT IMPLEMENTED");
		return false;
	}
}

package org.atriasoft.esvg.render;

import org.atriasoft.etk.math.Vector2f;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class ElementBezierCurveTo extends Element {
	public ElementBezierCurveTo(final boolean relative, final Vector2f pos1, final Vector2f pos) {
		super(PathType.BEZIER_CURVE_TO, relative);
		this.pos = pos;
		this.pos1 = pos1;
	}
	
	@Override
	public String display() {
		return "pos=" + this.pos + " pos1=" + this.pos1;
	}
}

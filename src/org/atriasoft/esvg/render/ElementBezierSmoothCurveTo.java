package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
import org.atriasoft.etk.math.Vector2f;

public class ElementBezierSmoothCurveTo extends Element {
	
	ElementBezierSmoothCurveTo(final boolean relative, final Vector2f pos) {
		super(PathType.bezierSmoothCurveTo, relative);
		this.pos = pos;
	}
	
	@Override
	public String display() {
		return "pos=" + this.pos;
	}
}

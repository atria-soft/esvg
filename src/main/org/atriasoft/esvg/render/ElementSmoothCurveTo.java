package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
import org.atriasoft.etk.math.Vector2f;

public class ElementSmoothCurveTo extends Element {
	public ElementSmoothCurveTo(final boolean relative, final Vector2f pos2, final Vector2f pos) {
		super(PathType.SMOOTH_CURVE_TO, relative);
		this.pos = pos;
		this.pos2 = pos2;
		
	}
	
	@Override
	public String display() {
		return "pos=" + this.pos + " pos2=" + this.pos2;
	}
}
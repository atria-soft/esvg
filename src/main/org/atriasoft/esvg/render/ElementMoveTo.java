package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
import org.atriasoft.etk.math.Vector2f;

public class ElementMoveTo extends Element {
	public ElementMoveTo(final boolean relative, final Vector2f pos) {
		super(PathType.MOVE_TO, relative);
		this.pos = pos;
		
	}
	
	@Override
	public String display() {
		return "pos=" + this.pos;
	}
}

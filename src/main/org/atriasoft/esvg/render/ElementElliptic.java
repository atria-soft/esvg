package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
import org.atriasoft.etk.math.Vector2f;

public class ElementElliptic extends Element {
	public float angle;
	public boolean largeArcFlag;
	public boolean sweepFlag;
	
	public ElementElliptic(final boolean relative, final Vector2f radius, // in this.pos1
			final float angle, final boolean largeArcFlag, final boolean sweepFlag, final Vector2f pos) {
		super(PathType.ELLIPTIC, relative);
		this.pos1 = radius;
		this.pos = pos;
		this.angle = angle;
		this.largeArcFlag = largeArcFlag;
		this.sweepFlag = sweepFlag;
	}
	
	@Override
	public String display() {
		return "pos=" + this.pos + " radius=" + this.pos1 + " angle=" + this.angle + " largeArcFlag=" + this.largeArcFlag + " sweepFlag=" + this.sweepFlag;
	}
}

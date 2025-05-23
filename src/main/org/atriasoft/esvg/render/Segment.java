package org.atriasoft.esvg.render;

import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Segment {
	
	public int direction;
	public Vector2f p0;
	public Vector2f p1;
	
	// TODO Update List to support not having it ...
	public Segment() {
		this.p0 = Vector2f.ZERO;
		this.p1 = Vector2f.ZERO;
		this.direction = 0;
	}
	
	public Segment(final Vector2f p0, final Vector2f p1) {
		// segment register all time the lower at P0n then we need to register the sens of the path
		this.p0 = p0;
		this.p1 = p1;
		this.direction = 0;
	}
	
	void applyMatrix(final Matrix2x3f transformationMatrix) {
		this.p0 = transformationMatrix.multiply(this.p0);
		this.p1 = transformationMatrix.multiply(this.p1);
		createDirection();
	}
	
	void createDirection() {
		if (this.p0.y() < this.p1.y()) {
			this.direction = 1; // direction like clock
		} else {
			Vector2f tmp = this.p0;
			this.p0 = this.p1;
			this.p1 = tmp;
			this.direction = -1; // direction like anti-clock
		}
	}
}

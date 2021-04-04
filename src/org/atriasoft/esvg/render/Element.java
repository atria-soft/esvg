package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

import org.atriasoft.etk.math.Vector2f;

public abstract class Element {
	protected PathType cmd;
	
	protected Vector2f pos = Vector2f.ZERO;
	
	protected Vector2f pos1 = Vector2f.ZERO;
	
	protected Vector2f pos2 = Vector2f.ZERO;
	
	protected boolean relative = false;
	
	public Element(final PathType type) {
		this.cmd = type;
		this.relative = false;
		
	}
	
	public Element(final PathType type, final boolean relative) {
		this.cmd = type;
		this.relative = relative;
		
	}
	
	public abstract String display();
	
	public Vector2f getPos() {
		return this.pos;
	}
	
	public Vector2f getPos1() {
		return this.pos1;
	}
	
	public Vector2f getPos2() {
		return this.pos2;
	}
	
	public boolean getRelative() {
		return this.relative;
	}
	
	public PathType getType() {
		return this.cmd;
	}
	
	public void setPos(final Vector2f val) {
		this.pos = val;
	}
	
	public void setPos1(final Vector2f val) {
		this.pos1 = val;
	}
	
	public void setPos2(final Vector2f val) {
		this.pos2 = val;
	}
	
	void setRelative(final boolean relative) {
		this.relative = relative;
	}
	
	@Override
	public String toString() {
		return "" + this.cmd + ": rel=" + getRelative() + " " + display();
	}
}

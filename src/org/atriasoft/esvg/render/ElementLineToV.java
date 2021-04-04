package org.atriasoft.esvg.render;

public class ElementLineToV extends Element {
	public ElementLineToV(final boolean relative, final float posY) {
		super(PathType.lineToV, relative);
		this.pos = this.pos.withY(posY);
	}
	
	@Override
	public String display() {
		return "posY=" + this.pos;
	}
}

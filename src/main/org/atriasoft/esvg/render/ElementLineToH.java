package org.atriasoft.esvg.render;

public class ElementLineToH extends Element {
	public ElementLineToH(final boolean relative, final float poX) {
		super(PathType.LINE_TO_H, relative);
		this.pos = this.pos.withX(poX);
	}
	
	@Override
	public String display() {
		return "posX=" + this.pos;
	}
}
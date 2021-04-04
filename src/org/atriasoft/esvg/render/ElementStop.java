package org.atriasoft.esvg.render;

public class ElementStop extends Element {
	ElementStop() {
		super(PathType.stop, false);
	}
	
	@Override
	public String display() {
		return "";
	}
}

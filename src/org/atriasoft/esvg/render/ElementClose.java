package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class ElementClose extends Element {
	ElementClose() {
		super(PathType.CLOSE, false);
	}
	
	ElementClose(final boolean relative) {
		super(PathType.CLOSE, relative);
	}
	
	@Override
	public String display() {
		return "";
	}
}

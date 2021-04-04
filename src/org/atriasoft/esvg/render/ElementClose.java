package org.atriasoft.esvg.render;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class ElementClose extends Element {
	ElementClose() {
		super(PathType.close, false);
	}
	
	ElementClose(final boolean relative) {
		super(PathType.close, relative);
	}
	
	@Override
	public String display() {
		return "";
	}
}

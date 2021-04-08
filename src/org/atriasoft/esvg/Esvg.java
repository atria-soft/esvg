package org.atriasoft.esvg;

import org.atriasoft.etk.Uri;

public class Esvg {
	public static void init() {
		Uri.addLibrary("esvg", Esvg.class, "/resources/esvg/");
	}
	
	private Esvg() {}
}

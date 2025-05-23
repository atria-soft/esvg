package org.atriasoft.esvg;

import org.atriasoft.etk.ConfigFont;
import org.atriasoft.etk.Configs;
import org.atriasoft.etk.Uri;

public class Esvg {
	public static void init() {
		Uri.addLibrary("esvg", Esvg.class, "/resources/esvg/");
		
		ConfigFont fonts = Configs.getConfigFonts();
		// add default Esvg fonts:
		fonts.add("FreeSherif", new Uri("FONTS", "FreeSherif.svg", "esvg"));
		fonts.add("FreeSans", new Uri("FONTS", "FreeSans.svg", "esvg"));
		fonts.add("FreeMono", new Uri("FONTS", "FreeMono.svg", "esvg"));
	}
	
	private Esvg() {}
}

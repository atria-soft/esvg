package org.atriasoft.esvg;

import org.atriasoft.etk.ConfigFont;
import org.atriasoft.etk.Configs;
import org.atriasoft.etk.Uri;

/**
 * Entry point for the esvg module.
 * <p>
 * Call {@link #init()} once at application startup to register the esvg resource library
 * and make the bundled SVG fonts (FreeSherif, FreeSans, FreeMono) available
 * through the {@link org.atriasoft.etk.ConfigFont} system.
 */
public class Esvg {

	/**
	 * Initialize the esvg module.
	 * <p>
	 * Registers the {@code "esvg"} resource library and adds the bundled SVG fonts
	 * (FreeSherif, FreeSans, FreeMono) to the global font configuration.
	 * Must be called before loading any SVG font.
	 */
	public static void init() {
		Uri.addLibrary("esvg", Esvg.class, "/resources/esvg/");
		final ConfigFont fonts = Configs.getConfigFonts();
		fonts.add("FreeSherif", new Uri("FONTS", "FreeSherif.svg", "esvg"));
		fonts.add("FreeSans", new Uri("FONTS", "FreeSans.svg", "esvg"));
		fonts.add("FreeMono", new Uri("FONTS", "FreeMono.svg", "esvg"));
	}

	private Esvg() {}
}

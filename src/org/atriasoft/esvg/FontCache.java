package org.atriasoft.esvg;

import java.util.HashMap;
import java.util.Map;

import org.atriasoft.etk.ConfigFont;
import org.atriasoft.etk.Configs;
import org.atriasoft.etk.Uri;

public class FontCache {
	private static final Map<String, EsvgFont> CACHE_FONTS = new HashMap<>();
	
	public static boolean existFont(final String fontName, final boolean bold, final boolean italic) {
		ConfigFont fontsConfigs = Configs.getConfigFonts();
		Uri baseUri = fontsConfigs.getFontUri(fontName);
		if (baseUri == null) {
			return false;
		}
		if (bold && italic) {
			Uri theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "BoldOblique.svg"), baseUri.getproperties());
			return theoricUri.exist();
		}
		if (bold && !italic) {
			Uri theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Bold.svg"), baseUri.getproperties());
			return theoricUri.exist();
		}
		if (!bold && italic) {
			Uri theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Oblique.svg"), baseUri.getproperties());
			return theoricUri.exist();
		}
		if (!bold && !italic) {
			Uri theoricUri = baseUri;
			return theoricUri.exist();
		}
		return false;
	}
	
	public static EsvgFont getFont(final String fontName, final boolean bold, final boolean italic) {
		String finalName = fontName + "__" + bold + "__" + italic;
		EsvgFont font = FontCache.CACHE_FONTS.get(finalName);
		if (font != null) {
			return font;
		}
		// try to find it:
		ConfigFont fontsConfigs = Configs.getConfigFonts();
		Uri baseUri = fontsConfigs.getFontUri(fontName);
		if (baseUri != null) {
			Uri theoricUri = null;
			if (bold && italic) {
				theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "BoldOblique.svg"), baseUri.getproperties());
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri == null || (bold && !italic)) {
				theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Bold.svg"), baseUri.getproperties());
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri == null || (!bold && italic)) {
				theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Oblique.svg"), baseUri.getproperties());
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri == null || (!bold && !italic)) {
				theoricUri = baseUri;
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri != null) {
				FontCache.CACHE_FONTS.put(finalName, EsvgFont.load(theoricUri));
				return FontCache.CACHE_FONTS.get(finalName);
			}
		}
		String defaultFontName = Configs.getConfigFonts().getName();
		if (defaultFontName.equals(fontName)) {
			return null;
		}
		return FontCache.getFont(defaultFontName, bold, italic);
	}
	
	private FontCache() {}
}

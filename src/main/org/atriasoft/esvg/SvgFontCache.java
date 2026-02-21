package org.atriasoft.esvg;

import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

import org.atriasoft.etk.ConfigFont;
import org.atriasoft.etk.Configs;
import org.atriasoft.etk.Uri;

/**
 * Cache for loaded SVG fonts.
 * Resolves font variants (bold, italic/oblique) and falls back to the default font.
 */
public class SvgFontCache {
	private static final Map<String, SvgFont> CACHE_FONTS = new ConcurrentHashMap<>();

	/**
	 * Check whether a font variant exists.
	 * @param fontName the font family name
	 * @param bold true for bold variant
	 * @param italic true for italic/oblique variant
	 * @return true if the font variant file exists
	 */
	public static boolean existFont(final String fontName, final boolean bold, final boolean italic) {
		final ConfigFont fontsConfigs = Configs.getConfigFonts();
		final Uri baseUri = fontsConfigs.getFontUri(fontName);
		if (baseUri == null) {
			return false;
		}
		if (bold && italic) {
			final Uri theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "BoldOblique.svg"), baseUri.getproperties());
			return theoricUri.exist();
		}
		if (bold) {
			final Uri theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Bold.svg"), baseUri.getproperties());
			return theoricUri.exist();
		}
		if (italic) {
			final Uri theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Oblique.svg"), baseUri.getproperties());
			return theoricUri.exist();
		}
		return baseUri.exist();
	}

	/**
	 * Get a cached font, loading it if necessary.
	 * Falls back to the default font if the requested variant is not available.
	 * @param fontName the font family name
	 * @param bold true for bold variant
	 * @param italic true for italic/oblique variant
	 * @return the font, or null if no font could be loaded
	 */
	public static SvgFont getFont(final String fontName, final boolean bold, final boolean italic) {
		final String finalName = fontName + "__" + bold + "__" + italic;
		final SvgFont cached = SvgFontCache.CACHE_FONTS.get(finalName);
		if (cached != null) {
			return cached;
		}
		// try to find the font
		final ConfigFont fontsConfigs = Configs.getConfigFonts();
		final Uri baseUri = fontsConfigs.getFontUri(fontName);
		if (baseUri != null) {
			Uri theoricUri = null;
			if (bold && italic) {
				theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "BoldOblique.svg"), baseUri.getproperties());
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri == null && bold) {
				theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Bold.svg"), baseUri.getproperties());
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri == null && italic) {
				theoricUri = new Uri(baseUri.getGroup(), baseUri.getPath().replace(".svg", "Oblique.svg"), baseUri.getproperties());
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri == null) {
				theoricUri = baseUri;
				if (!theoricUri.exist()) {
					theoricUri = null;
				}
			}
			if (theoricUri != null) {
				final SvgFont loaded = SvgFont.load(theoricUri);
				if (loaded != null) {
					SvgFontCache.CACHE_FONTS.put(finalName, loaded);
				}
				return loaded;
			}
		}
		// Fallback to default font
		final String defaultFontName = Configs.getConfigFonts().getName();
		if (Objects.equals(defaultFontName, fontName)) {
			return null;
		}
		return SvgFontCache.getFont(defaultFontName, bold, italic);
	}

	private SvgFontCache() {}
}

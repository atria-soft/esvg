package test.atriasoft.esvg;

import org.atriasoft.esvg.Esvg;
import org.atriasoft.esvg.SvgFont;
import org.atriasoft.esvg.raster.GlyphRaster;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestFont {

	@Test
	public void testFontRead() {
		Esvg.init();
		final SvgFont font = SvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		Assertions.assertTrue(font.getNumGlyphs() > 0);
	}

	@Test
	public void testFontRenderSingleGlyph() {
		Esvg.init();
		final SvgFont font = SvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		final GlyphRaster out = font.render('E', 25);
		Assertions.assertNotNull(out);
		Assertions.assertTrue(out.getWidth() > 0);
		Assertions.assertTrue(out.getHeight() > 0);
	}

	@Test
	public void testFontRenderMultipleGlyphs() {
		Esvg.init();
		final SvgFont font = SvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		// Test various characters
		for (final char c : new char[]{'E', 'e', 'p', 'f', 'A', 'g'}) {
			final GlyphRaster out = font.render(c, 25);
			Assertions.assertNotNull(out, "Failed to render glyph: " + c);
		}
	}

	@Test
	public void testFontRenderString() {
		Esvg.init();
		final SvgFont font = SvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		final GlyphRaster out = font.render("Hello", 100, false);
		Assertions.assertNotNull(out);
		Assertions.assertTrue(out.getWidth() > 0);
		Assertions.assertTrue(out.getHeight() > 0);
	}

	@Test
	public void testFontRenderStringWithKerning() {
		Esvg.init();
		final SvgFont font = SvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		final GlyphRaster out = font.render("VA", 100, true);
		Assertions.assertNotNull(out);
		Assertions.assertTrue(out.getWidth() > 0);
	}

	@Test
	public void testFontMetrics() {
		Esvg.init();
		final SvgFont font = SvgFont.load(new Uri("FONTS", "FreeSherif.svg", "esvg"));
		Assertions.assertNotNull(font);
		final int height = font.calculateFontRealHeight(25);
		Assertions.assertTrue(height > 0);
		final int width = font.calculateWidth('A', 25);
		Assertions.assertTrue(width > 0);
	}
}

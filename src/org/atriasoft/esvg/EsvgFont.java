package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.atriasoft.esvg.font.Glyph;
import org.atriasoft.esvg.font.Kerning;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.esvg.render.RenderingConfig;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.exml.Exml;
import org.atriasoft.exml.exception.ExmlException;
import org.atriasoft.exml.model.XmlElement;
import org.atriasoft.exml.model.XmlNode;

// https://www.w3.org/TR/SVGTiny12/fonts.html

/*
                             |            |          |            |
                             |            |          |            |
                             |            |          |            |
                      Y      |            |          |            |
                      ^      |------------|          |------------|
                      |
    advance.y:   /->  |
                 |    |
                 |    |
 sizeTex.x /->   |    |         |------------|          |------------|
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |     A      |          |     G      |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           |     |    |         |            |          |            |
           \->   |    |         |------------|          |------------|
        /-->     |    |
        \-->     \->  |
  bearing.y           |
                      |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   X
                           <------------------------> : advance.x
                                <------------> : sizeTexture.x
                           <---> : bearing.x
                       

                                                                          
                                                                          
                                                                          
                                                         _
                              *----------------------*   ^ ==> calculateFontRealHeight(fontSize);
                              |                      |   |   ^ ==> getAscent(fontSize);
                              |                      |   |   |    _
                              |          /\          |   |   |    ^ ==> Font Height (height of a capital letter) = fontSize
                              |         /  \         |   |   |    |
                              |        /    \        |   |   |    |
                              |       /------\       |   |   |    |
                              |      /        \      |   |   |    |
                              |     /          \     |   |___|____|________________________==> render line
                              |                      |   |                ^
                              |                      |   |                |
                              |                      |   |                |==> getDescent(fontSize);
                              |                      |   |                |
                              *----------------------*   |                |
                                                                          
                                        
*/

public class EsvgFont {
	
	/**
	 * Load the file that might contain the svg
	 * @param uri File of the svg
	 * @return false : An error occured
	 * @return true : Parsing is OK
	 */
	public static EsvgFont load(final Uri uri) {
		final EsvgFont font = new EsvgFont();
		XmlNode doc = null;
		try {
			doc = Exml.parse(uri);
		} catch (final ExmlException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
		if (!(doc instanceof final XmlElement root)) {
			Log.error("can not load the SVG font ==> wrong root node");
			return null;
		}
		if (!root.existNode("svg") || !(root.getNodeNoExcept("svg") instanceof final XmlElement svgNode)) {
			Log.error("can not load Node <svg> in svg document");
			return null;
		}
		if (!svgNode.existNode("defs") || !(svgNode.getNodeNoExcept("defs") instanceof final XmlElement defsNode)) {
			Log.error("can not load Node <defs> in svg document");
			return null;
		}
		if (!defsNode.existNode("font") || !(defsNode.getNodeNoExcept("font") instanceof final XmlElement fontElement)) {
			Log.error("can not load Node <font> in svg document");
			return null;
		}
		
		font.horizAdvX = Integer.parseInt(fontElement.getAttribute("horiz-adv-x", "100"));
		
		int nbGlyph = 0;
		for (final XmlNode values : fontElement.getNodes()) {
			if (values.getValue().equals("font-face")) {
				if (values instanceof final XmlElement fontFace) {
					font.fontFamily = fontFace.getAttribute("font-family", "unknown");
					font.fontStretch = fontFace.getAttribute("font-stretch", "normal");
					font.fontWeight = Integer.parseInt(fontFace.getAttribute("font-weight", "400"));
					font.unitsPerEm = Integer.parseInt(fontFace.getAttribute("units-per-em", "1000"));
					font.ascent = Integer.parseInt(fontFace.getAttribute("ascent", "800"));
					font.descent = Integer.parseInt(fontFace.getAttribute("descent", "-200"));
					font.xHeight = Integer.parseInt(fontFace.getAttribute("x-height", "450"));
					font.capHeight = Integer.parseInt(fontFace.getAttribute("cap-height", "662"));
					font.underlineThickness = Integer.parseInt(fontFace.getAttribute("underline-thickness", "50"));
					font.underlinePosition = Integer.parseInt(fontFace.getAttribute("underline-position", "-150"));
					//panose-1="2 2 6 3 5 4 5 2 3 4"
					String tmp = fontFace.getAttribute("panose-1", null);
					String[] tmpSplit = tmp.split(" ");
					font.panose1 = new int[tmpSplit.length];
					for (int iii = 0; iii < tmpSplit.length; iii++) {
						font.panose1[iii] = Integer.parseInt(tmpSplit[iii]);
					}
					//bbox="-879 -545 1767 934"
					tmp = fontFace.getAttribute("bbox", null);
					tmpSplit = tmp.split(" ");
					font.bbox = new int[tmpSplit.length];
					for (int iii = 0; iii < tmpSplit.length; iii++) {
						font.bbox[iii] = Integer.parseInt(tmpSplit[iii]);
					}
					//unicode-range="U+0020-1F093"
					tmp = fontFace.getAttribute("unicode-range", null);
					tmpSplit = tmp.split("-");
					final int start = Integer.parseInt(tmpSplit[0].substring(2), 16);
					final int stop = Integer.parseInt(tmpSplit[1], 16);
					font.unicodeRange = new Pair<>(start, stop);
				}
			}
		}
		for (final XmlNode values : fontElement.getNodes()) {
			if (values.getValue().equals("glyph")) {
				nbGlyph++;
				//Log.info("find flyph: " + nbGlyph);
				final Glyph tmp = Glyph.valueOf(values.toElement(), font);
				if (tmp != null) {
					font.glyphs.put(tmp.getUnicodeValue(), tmp);
				}
			} else if (values.getValue().equals("hkern")) {
				// check later ...
			} else if (values.getValue().equals("missing-glyph")) {
				font.missingGlyph = Glyph.valueOf(values.toElement(), font);
			} else if (values.getValue().equals("font-face")) {
				// already done ...
			} else {
				Log.warning("unsupported node name :" + values.getValue());
			}
		}
		for (final XmlNode values : fontElement.getNodes()) {
			if (values.getValue().equals("hkern")) {
				if (values instanceof final XmlElement kernElem) {
					final String g1 = kernElem.getAttribute("g1", null);
					final String g2 = kernElem.getAttribute("g2", null);
					if (g1 == null || g2 == null) {
						continue;
					}
					final float offset = Float.parseFloat(kernElem.getAttribute("k", "0"));
					if (offset == 0.0f) {
						continue;
					}
					final String[] g1Splited = g1.split(",");
					final String[] g2Splited = g2.split(",");
					// create the list of kerning of the next elements
					final List<Kerning> elementsKerning = new ArrayList<>();
					for (int iii = 0; iii < g2Splited.length; iii++) {
						for (final Map.Entry<Integer, Glyph> entry : font.glyphs.entrySet()) {
							if (entry.getValue().getName().equals(g2Splited[iii])) {
								elementsKerning.add(new Kerning(offset, entry.getKey()));
								break;
							}
						}
					}
					// add it on the
					for (int iii = 0; iii < g1Splited.length; iii++) {
						for (final Map.Entry<Integer, Glyph> entry : font.glyphs.entrySet()) {
							if (entry.getValue().getName().equals(g1Splited[iii])) {
								entry.getValue().addKerning(elementsKerning);
								font.hasKerning = true;
								break;
							}
						}
					}
				}
			}
		}
		return font;
	}
	
	// The maximum accented height of the font within the font coordinate system.
	private int ascent = 800; // this is the height of the font (on top...)
	private int[] bbox = { -879, -545, 1767, 934 };
	// The height of uppercase glyphs in the font within the font coordinate system.
	private int capHeight = 662;
	// The maximum unaccented depth of the font within the font coordinate system.
	private int descent = -200; // lower size of the font
	private String fontFamily = "unknown";
	private String fontStretch = "normal";
	private int fontWeight = 400;
	private final Map<Integer, Glyph> glyphs = new HashMap<>();
	private boolean hasKerning = false;
	// The horizontal advance after rendering the glyph in horizontal orientation. If the attribute is not specified, the effect is as if the attribute were set to the value of the font's 'horiz-adv-x' attribute.
	// Glyph widths are required to be non-negative, even if the glyph is typically rendered right-to-left, as in Hebrew and Arabic scripts.
	private int horizAdvX = 100;
	private Glyph missingGlyph = null;
	private int[] panose1 = { 2, 2, 6, 3, 5, 4, 5, 2, 3, 4 };
	private int underlinePosition = -150;
	private int underlineThickness = 50;
	private Pair<Integer, Integer> unicodeRange = new Pair<>(0x0020, 0x1F093);
	private int unitsPerEm = 1000; // full size of the font
	// The height of lowercase glyphs in the font within the font coordinate system.
	private int xHeight = 450;
	
	/**
	 * Get the font real size use (height) for all the characters.
	 * @param fontSize size of the font the user require
	 * @return Real size in pixel of element can impact the output
	 */
	public int calculateFontRealHeight(final int fontSize) {
		return fontSize * this.unitsPerEm / this.capHeight;
		
	}
	
	public float calculateFontSizeWithHeight(final float fontHeight) {
		return fontHeight * this.capHeight / this.unitsPerEm;
	}
	
	public Vector2f calculateRenderOffset(final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		final float deltaY = realSize * this.ascent / this.unitsPerEm;
		return new Vector2f(0, deltaY);
	}
	
	public float calculateSclaleFactor(final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		return (float) realSize / (float) this.unitsPerEm;
	}
	
	public Vector2i calculateTextSize(final int fontSize, final String data) {
		final boolean withKerning = true;
		final int widthOut = calculateWidth(data, fontSize, withKerning);
		
		final int realSize = calculateFontRealHeight(fontSize);
		return new Vector2i(widthOut, realSize);
		/*
		float scale = (float) realSize / (float) this.unitsPerEm;
				
		int offsetWriting = 0;
		int lastValue = 0;
		for (char uVal : data.toCharArray()) {
			Glyph glyph = getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				lastValue = uVal;
			}
			
			float advenceXLocal = glyph.getHorizAdvX() * scale;
			// No generation of output ...
			offsetWriting += advenceXLocal;
		}
		return new Vector2i(offsetWriting, realSize);
		*/
	}
	
	public int calculateWidth(final int uVal, final int fontSize) {
		final Glyph glyph = getGlyph(uVal);
		if (glyph == null) {
			return 0;
		}
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		return (int) (glyph.getHorizAdvX() * scale);
	}
	
	public int calculateWidth(final String uVal, final int fontSize) {
		return calculateWidth(uVal, fontSize, true);
	}
	
	public int calculateWidth(final String data, final int fontSize, final boolean withKerning) {
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		//Log.error("scale =" + scale+ " font size = " + fontSize + "  realSize=" + realSize);
		float offsetWriting = 0;
		int lastValue = 0;
		for (final char uVal : data.toCharArray()) {
			final Glyph glyph = getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				lastValue = uVal;
			}
			
			final float advenceXLocal = glyph.getHorizAdvX() * scale;
			offsetWriting += advenceXLocal;
			//Log.error("offset X =" + offsetWriting + " + " + advenceXLocal + "    " + uVal);
		}
		return (int) offsetWriting;
	}
	
	/**
	 * Get the rendering size of the specific glyph (size rendered in the Weight class).
	 * @param unicodeValue Unicode value to render
	 * @param fontSize Size of the font
	 * @return the size in pixel of the rendering elements
	 */
	public Vector2i calculateWidthRendering(final Integer unicodeValue, final int fontSize) {
		return new Vector2i(calculateWidth(unicodeValue, fontSize), calculateFontRealHeight(fontSize));
	}
	
	public int getDescent() {
		return this.descent;
	}
	
	public Glyph getGlyph(final int glyphIndex) {
		final Glyph out = this.glyphs.get(glyphIndex);
		if (out == null) {
			return this.missingGlyph;
		}
		return out;
	}
	
	public Glyph getGlyphNullIfMissing(final int glyphIndex) {
		final Glyph out = this.glyphs.get(glyphIndex);
		if (out == null) {
			return null;
		}
		return out;
	}
	
	public int getHorizAdvX() {
		return this.horizAdvX;
	}
	
	/**
	 * Get the number of available glyph in the Font
	 * @return the glyph count.
	 */
	public int getNumGlyphs() {
		return this.glyphs.size();
	}
	
	public float getUnitsPerEm() {
		return this.unitsPerEm;
	}
	
	/**
	 * Check if the font have some kerning data
	 * @return true if kerning is availlable.
	 */
	public boolean hasKerning() {
		return this.hasKerning;
	}
	
	public Weight render(final int uVal, final int fontSize) {
		final int realSize = calculateFontRealHeight(fontSize);
		final Glyph glyph = getGlyph(uVal);
		if (glyph == null) {
			return null;
		}
		final float scale = (float) realSize / (float) this.unitsPerEm;
		final RenderingConfig config = new RenderingConfig(10, 0.25f, 8);
		final Matrix2x3f transform = Matrix2x3f.createTranslate(new Vector2f(0, -this.descent)).multiply(Matrix2x3f.createScale(scale));
		final PathModel model = glyph.getModel();
		if (model == null) {
			return null;
		}
		final Weight data = glyph.getModel().drawFill(calculateWidthRendering(uVal, fontSize), transform, 8, config);
		return data;
	}
	
	public Weight render(final String uVal, final int fontSize) {
		return render(uVal, fontSize, true);
	}
	
	public Weight render(final String data, final int fontSize, final boolean withKerning) {
		final int widthOut = calculateWidth(data, fontSize, withKerning);
		
		final int realSize = calculateFontRealHeight(fontSize);
		final float scale = (float) realSize / (float) this.unitsPerEm;
		
		final Weight weight = new Weight(new Vector2i(widthOut, realSize));
		
		float offsetWriting = 0;
		int lastValue = 0;
		for (final char uVal : data.toCharArray()) {
			final Glyph glyph = getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				Log.info("    ==> kerning offset = " + (glyph.getKerning(lastValue) * scale));
				lastValue = uVal;
			}
			
			final float advenceXLocal = glyph.getHorizAdvX() * scale;
			
			final RenderingConfig config = new RenderingConfig(10, 0.25f, 8);
			final Matrix2x3f transform = Matrix2x3f.createTranslate(new Vector2f(0, -this.descent)).multiply(Matrix2x3f.createScale(scale));
			final PathModel model = glyph.getModel();
			if (model != null) {
				final Weight redered = model.drawFill(calculateWidthRendering((int) uVal, fontSize), transform, 8, config);
				weight.fusion(redered, (int) offsetWriting, 0);
			}
			offsetWriting += advenceXLocal;
			
		}
		return weight;
	}
}

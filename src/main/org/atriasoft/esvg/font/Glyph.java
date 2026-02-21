package org.atriasoft.esvg.font;

import java.awt.Shape;
import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.SvgPathParser;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Represents a single glyph in an SVG font.
 * <p>
 * A glyph holds the SVG path data for the character outline, its horizontal advance width,
 * kerning information, and Unicode mapping. The {@link java.awt.Shape} is lazily parsed
 * from the SVG path data on first access via {@link #getShape()}.
 *
 * @see Kerning
 * @see org.atriasoft.esvg.SvgFont
 */
public class Glyph {
	static final Logger LOGGER = LoggerFactory.getLogger(Glyph.class);

	private int horizAdvX;
	private List<Kerning> kernings = new ArrayList<>();
	private volatile Shape shape;
	private String name;
	private final String path;
	private String unicode;

	private int unicodeValue;

	/**
	 * Create a new glyph.
	 * @param horizAdvX the horizontal advance width in font units
	 * @param path the SVG path data string ({@code d} attribute), may be null
	 * @param name the glyph name (from {@code glyph-name} attribute)
	 * @param unicode the Unicode character as a string
	 * @param unicodeValue the Unicode code point
	 */
	public Glyph(final int horizAdvX, final String path, final String name, final String unicode,
			final int unicodeValue) {
		this.horizAdvX = horizAdvX;
		this.shape = null;
		this.path = path;
		this.name = name;
		this.unicode = unicode;
		this.unicodeValue = unicodeValue;
	}

	/**
	 * Add kerning pairs to this glyph.
	 * @param elementsKerning the kerning entries to add
	 */
	public void addKerning(final List<Kerning> elementsKerning) {
		this.kernings.addAll(elementsKerning);
	}

	/**
	 * Get the horizontal advance width in font units.
	 * @return the advance width
	 */
	public int getHorizAdvX() {
		return this.horizAdvX;
	}

	/**
	 * Get the kerning offset between this glyph and a preceding character.
	 * @param unicodeValue the Unicode code point of the preceding character
	 * @return the kerning offset in font units, or 0 if no kerning pair exists
	 */
	public float getKerning(final int unicodeValue) {
		if (unicodeValue == 0) {
			return 0.0f;
		}
		for (final Kerning elem : this.kernings) {
			if (elem.unicode() == unicodeValue) {
				LOGGER.trace("Get kerning between : '{}' and '{}'  => {}", (char) this.unicodeValue, (char) unicodeValue, elem.offset());
				return elem.offset();
			}
		}
		return 0;
	}

	/**
	 * Get all kerning entries for this glyph.
	 * @return the list of kerning pairs
	 */
	public List<Kerning> getKernings() {
		return this.kernings;
	}

	/**
	 * Get the Java2D shape for this glyph, lazily parsed from the SVG path data.
	 * @return the glyph shape, or null if no path data is available
	 */
	public Shape getShape() {
		if (this.shape == null && this.path != null) {
			this.shape = SvgPathParser.parsePath(this.path);
		}
		return this.shape;
	}

	/**
	 * Get the glyph name (from the {@code glyph-name} SVG attribute).
	 * @return the glyph name, or null
	 */
	public String getName() {
		return this.name;
	}

	/**
	 * Get the Unicode character as a string.
	 * @return the unicode string
	 */
	public String getUnicode() {
		return this.unicode;
	}

	/**
	 * Get the Unicode code point.
	 * @return the code point value
	 */
	public Integer getUnicodeValue() {
		return this.unicodeValue;
	}

	/** Set the horizontal advance width. */
	public void setHorizAdvX(final int horizAdvX) {
		this.horizAdvX = horizAdvX;
	}

	/** Set the kerning entries. */
	public void setKernings(final List<Kerning> kernings) {
		this.kernings = kernings;
	}

	/** Set the glyph name. */
	public void setName(final String name) {
		this.name = name;
	}

	/** Set the Unicode character string. */
	public void setUnicode(final String unicode) {
		this.unicode = unicode;
	}

	/** Set the Unicode code point. */
	public void setUnicodeValue(final int unicodeValue) {
		this.unicodeValue = unicodeValue;
	}
}

package org.atriasoft.esvg.font;

import java.awt.Shape;
import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.render.SvgPathToShape;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Glyph {
	static final Logger LOGGER = LoggerFactory.getLogger(Glyph.class);

	private int horizAdvX;
	private List<Kerning> kernings = new ArrayList<>();
	private Shape shape;
	private String name;
	private final String path;
	private String unicode;

	private int unicodeValue;

	public Glyph(final int horizAdvX, final String path, final String name, final String unicode,
			final int unicodeValue) {
		this.horizAdvX = horizAdvX;
		this.shape = null;
		this.path = path;
		this.name = name;
		this.unicode = unicode;
		this.unicodeValue = unicodeValue;
	}

	public void addKerning(final List<Kerning> elementsKerning) {
		this.kernings.addAll(elementsKerning);
	}

	public int getHorizAdvX() {
		return this.horizAdvX;
	}

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

	public List<Kerning> getKernings() {
		return this.kernings;
	}

	public Shape getShape() {
		if (this.shape == null && this.path != null) {
			this.shape = SvgPathToShape.parsePath(this.path);
		}
		return this.shape;
	}

	public String getName() {
		return this.name;
	}

	public String getUnicode() {
		return this.unicode;
	}

	public Integer getUnicodeValue() {
		return this.unicodeValue;
	}

	public void setHorizAdvX(final int horizAdvX) {
		this.horizAdvX = horizAdvX;
	}

	public void setKernings(final List<Kerning> kernings) {
		this.kernings = kernings;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setUnicode(final String unicode) {
		this.unicode = unicode;
	}

	public void setUnicodeValue(final int unicodeValue) {
		this.unicodeValue = unicodeValue;
	}

}

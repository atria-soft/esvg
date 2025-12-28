package org.atriasoft.esvg.font;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.EsvgFont;
import org.atriasoft.esvg.Path;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.exml.model.XmlElement;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Glyph {
	private static final boolean LAZY_MODE = true;
	static final Logger LOGGER = LoggerFactory.getLogger(Glyph.class);

	public static Glyph valueOf(final XmlElement element) {
		return Glyph.valueOf(element, null);
	}

	public static Glyph valueOf(final XmlElement element, final EsvgFont font) {
		if (element == null) {
			return null;
		}
		final String name = element.getAttribute("glyph-name", null);
		LOGGER.trace("get glyph name = '{}'", name);
		final String tmpValue = element.getAttribute("horiz-adv-x", null);
		int horizAdvX = font == null ? 100 : font.getHorizAdvX();
		if (tmpValue != null && tmpValue.length() != 0) {
			horizAdvX = Integer.parseInt(tmpValue);
		}
		LOGGER.trace("        horizAdvX= '{}'", horizAdvX);
		final String unicode = element.getAttribute("unicode", null);
		LOGGER.trace("        unicode= '{}'", unicode);
		if (unicode == null) {
			LOGGER.debug("Not manage glyph : '{}' (missing unicode value)", name);
			return null;
		}
		final String d = element.getAttribute("d", null);
		LOGGER.trace("        d= '{}'", d);
		int unicodeValue = 0;
		if (unicode.startsWith("&#x") && unicode.endsWith(";")) {
			final String subElement = unicode.substring(3, unicode.length() - 1);
			if (subElement.indexOf("&") != -1) {
				LOGGER.debug("not supported glyph concatenarion {} value='{}'", name, unicode);
				return null;
			}
			unicodeValue = Integer.parseInt(subElement, 16);
		} else if (unicode.startsWith("&#") && unicode.endsWith(";")) {
			final String subElement = unicode.substring(2, unicode.length() - 1);
			if (subElement.indexOf("&") != -1) {
				LOGGER.debug("not supported glyph concatenarion {} value='{}'", name, unicode);
				return null;
			}
			unicodeValue = Integer.parseInt(subElement, 16);
		} else if (unicode.length() != 1) {
			LOGGER.debug("not supported glyph concatenarion {} value='{}'", name, unicode);
			return null;
		} else {
			unicodeValue = unicode.charAt(0);
		}
		LOGGER.trace("        unicodeValue= '{}'", unicodeValue);
		final Glyph out = new Glyph(horizAdvX, d, name, unicode, unicodeValue);
		if (!Glyph.LAZY_MODE) {
			// when not in lazy mode we force the parsing of the model, this permit to check the whole font... otherwise many font is really big > 8000 glyph, then it is a waste of time...
			out.getModel();
		}
		return out;
	}

	private int horizAdvX;
	private List<Kerning> kernings = new ArrayList<>();
	private PathModel model;
	private String name;
	private final String path;
	private String unicode;

	private int unicodeValue;

	public Glyph(final int horizAdvX, final PathModel model, final String name, final String unicode,
			final int unicodeValue) {
		this.horizAdvX = horizAdvX;
		this.model = model;
		this.path = null;
		this.name = name;
		this.unicode = unicode;
		this.unicodeValue = unicodeValue;
	}

	public Glyph(final int horizAdvX, final String path, final String name, final String unicode,
			final int unicodeValue) {
		this.horizAdvX = horizAdvX;
		this.model = null;
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

	public PathModel getModel() {
		if (this.model == null && this.path != null) {
			this.model = Path.createPathModel(this.path);
		}
		return this.model;
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

	public void setModel(final PathModel model) {
		this.model = model;
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

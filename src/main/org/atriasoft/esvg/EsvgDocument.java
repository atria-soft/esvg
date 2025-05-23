package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.aknot.exception.AknotException;
import org.atriasoft.egami.ImageFloatRGBA;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.exml.Exml;
import org.atriasoft.exml.exception.ExmlException;
import org.atriasoft.exml.exception.ExmlNodeDoesNotExist;
import org.atriasoft.exml.model.XmlElement;
import org.atriasoft.exml.model.XmlNode;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class EsvgDocument extends Base {
	static final Logger LOGGER = LoggerFactory.getLogger(EsvgDocument.class);
	private boolean loadOK = false;
	private final List<Base> refList = new ArrayList<>();
	private Vector2f size = Vector2f.ZERO;
	private final List<Base> subElementList = new ArrayList<>();
	private String title = ""; //!< sub-element list
	private Uri uri = null; //!< reference elements ...
	private String version = "0.0";

	public EsvgDocument() {

	}

	public EsvgDocument(final Vector2i size) {
		this.size = new Vector2f(size.x(), size.y());
	}

	public void addElement(final Base elem) {
		this.subElementList.add(elem);
	}

	/**
	 * change all style in a xml atribute
	 */
	public boolean cleanStyleProperty(final XmlElement root) {
		// for each nodes:
		for (final XmlNode it : root.getNodes()) {
			if (!(it instanceof final XmlElement child)) {
				continue;
			}
			// get attribute style:
			if (child.existAttribute("style")) {
				final String content = child.getAttribute("style", "");
				if (content.length() != 0) {
					final String[] listStyle = content.split(";");
					for (final String it1 : listStyle) {
						final String[] value = it1.split(":");
						if (value.length != 2) {
							LOGGER.error("parsing style with a wrong patern : " + it1 + " missing ':'");
							continue;
						}
						// TODO Check if the attibute already exist ...
						child.setAttribute(value[0], value[1]);
					}
				}
				// remove attribute style:
				child.removeAttribute("style");
			}
			// sub-parsing ...
			cleanStyleProperty(child);
		}
		return true;
	}

	public void clear() {
		this.uri = null;
		this.version = "0.0";
		this.loadOK = true;
		this.paint.clear();
		this.size = Vector2f.ZERO;
	}

	/**
			 * Display all the node in the svg file.
			 */
	public void displayDebug() {
		LOGGER.debug("Main SVG: size=" + this.size);
		LOGGER.debug("    refs:");
		for (final Base element : this.refList) {
			if (element != null) {
				element.display(2);
			}
		}
		LOGGER.debug("    Nodes:");
		for (final Base element : this.subElementList) {
			if (element != null) {
				element.display(2);
			}
		}
	}

	@Override
	protected void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		for (final Base element : this.subElementList) {
			if (element != null) {
				element.draw(myRenderer, basicTrans);
			}
		}
	}

	@Override
	protected void drawShapePoints(
			final List<List<Vector2f>> out,
			final int recurtionMax,
			final float threshold,
			final Matrix2x3f basicTrans,
			final int level) {
		LOGGER.trace(spacingDist(level) + "DRAW shape EsvgDocument");
		for (final Base it : this.subElementList) {
			if (it != null) {
				it.drawShapePoints(out, recurtionMax, threshold, basicTrans, level + 1);
			}
		}
	}

	// TODO remove this fucntion : use generic function ...
	public Vector2f getDefinedSize() {
		return this.size;
	}

	public List<List<Vector2f>> getLines() {
		return getLines(new Vector2f(256, 256));
	}

	public List<List<Vector2f>> getLines(Vector2f size) {
		final List<List<Vector2f>> out = new ArrayList<>();
		if (size.x() <= 0) {
			size = size.withX(this.size.x());
		}
		if (size.y() <= 0) {
			size = size.withY(this.size.y());
		}
		LOGGER.debug("lineification size " + size);
		// create the first element matrix modification ...
		final Matrix2x3f basicTrans = Matrix2x3f.IDENTITY
				.multiply(Matrix2x3f.createScale(new Vector2f(size.x() / this.size.x(), size.y() / this.size.y())));
		drawShapePoints(out, 10, 0.25f, basicTrans);
		return out;
	}

	public Base getReference(final String name) {
		if (name.isEmpty()) {
			LOGGER.error("request a reference with no name ... ");
			return null;
		}
		for (final Base it : this.refList) {
			if (it == null) {
				continue;
			}
			if (it.getId().equals(name)) {
				return it;
			}
		}
		LOGGER.error("Can not find reference name : '" + name + "'");
		return null;
	}

	public boolean isLoadOk() {
		return this.loadOK;
	}

	/*
	//! @previous
	public List<Color> renderImageFloatRGB(final Vector2i size) {
		List<Color> data = renderImageFloatRGBA(size);
		// Reduce scope:
		List<Color<float,3>> out;
		out.resize(data.size());
		for (sizet iii=0; iii<data.size(); ++iii) {
			out[iii] = data[iii];
		}
		return out;
	}

	//! @previous
	public List<Color<uint8t,4>> renderImageU8RGBA(final Vector2i size) {
		List<Color> data = renderImageFloatRGBA(size);
		// Reduce scope:
		List<Color<uint8t,4>> out;
		out.resize(data.size());
		for (sizet iii=0; iii<data.size(); ++iii) {
			out[iii] = data[iii];
		}
		return out;
	}

	//! @previous
	public List<Color<uint8t,3>> renderImageU8RGB(final Vector2i size) {
		List<Color> data = renderImageFloatRGBA(size);
		// Reduce scope:
		List<Color<uint8t,3>> out;
		out.resize(data.size());
		for (sizet iii=0; iii<data.size(); ++iii) {
			out[iii] = data[iii];
		}
		return out;
	}
	*/
	/**
	 * Load the file that might contain the svg
	 * @param uri File of the svg
	 * @return false : An error occured
	 * @return true : Parsing is OK
	 */
	public boolean load(final Uri uri) {
		clear();
		this.uri = uri;
		XmlNode doc = null;
		try {
			doc = Exml.parse(uri);
		} catch (final ExmlException | AknotException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		if (doc instanceof final XmlElement elem && elem.existNode("svg")) {
			try {
				if (elem.getNode("svg") instanceof final XmlElement rootElement) {
					cleanStyleProperty(rootElement);
					this.loadOK = parseXMLData(rootElement);
				}
			} catch (final ExmlNodeDoesNotExist e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
		}
		return this.loadOK;
	}

	/**
	 * parse a string that contain an svg stream
	 * @param data Data to parse
	 * @return false : An error occured
	 * @return true : Parsing is OK
	 */
	public boolean parse(final String data) {
		clear();
		this.uri = null;
		XmlNode doc = null;
		try {
			doc = Exml.parse(data);
		} catch (final ExmlException | AknotException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		if (doc instanceof final XmlElement elem && elem.existNode("svg")) {
			try {
				if (elem.getNode("svg") instanceof final XmlElement rootElement) {
					cleanStyleProperty(rootElement);
					this.loadOK = parseXMLData(rootElement);
				}
			} catch (final ExmlNodeDoesNotExist e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
		}
		return this.loadOK;
	}

	public boolean parseXMLData(final XmlElement root) {
		return parseXMLData(root, false);
	}

	public boolean parseXMLData(final XmlElement root, final boolean isReference) {
		// get the svg version :
		this.version = root.getAttribute("version", "");
		// parse ...
		Vector2f pos = Vector2f.ZERO;
		if (!isReference) {
			parseTransform(root);
			pos = parseXmlPosition(root);
			this.size = parseXmlSize(root);
			parsePaintAttr(root);
			LOGGER.trace("parsed .ROOT trans: " + this.transformMatrix);
		} else {
			LOGGER.trace("Parse Reference section ... (no attibute)");
		}

		Vector2f maxSize = Vector2f.ZERO;
		final Dynamic<Vector2f> size = new Dynamic<>(Vector2f.ZERO);
		// parse all sub node:
		for (final XmlNode it : root.getNodes()) {
			if (!(it instanceof final XmlElement child)) {
				// comment can be here...
				continue;
			}
			Base elementParser = null;
			if (child.getValue().equals("g")) {
				elementParser = new Group(this.paint);
			} else if (child.getValue().equals("a")) {
				LOGGER.info("Note : 'a' balise is parsed like a g balise ...");
				elementParser = new Group(this.paint);
			} else if (child.getValue().equals("title")) {
				this.title = "TODO : set the title here ...";
				continue;
			} else if (child.getValue().equals("path")) {
				elementParser = new Path(this.paint);
			} else if (child.getValue().equals("rect")) {
				elementParser = new Rectangle(this.paint);
			} else if (child.getValue().equals("circle")) {
				elementParser = new Circle(this.paint);
			} else if (child.getValue().equals("ellipse")) {
				elementParser = new Ellipse(this.paint);
			} else if (child.getValue().equals("line")) {
				elementParser = new Line(this.paint);
			} else if (child.getValue().equals("polyline")) {
				elementParser = new Polyline(this.paint);
			} else if (child.getValue().equals("polygon")) {
				elementParser = new Polygon(this.paint);
			} else if (child.getValue().equals("text")) {
				elementParser = new Text(this.paint);
			} else if (child.getValue().equals("radialGradient")) {
				if (!isReference) {
					LOGGER.error("'" + child.getValue() + "' node must not be defined outside a defs Section");
					continue;
				}
				elementParser = new RadialGradient(this.paint);
			} else if (child.getValue().equals("linearGradient")) {
				if (!isReference) {
					LOGGER.error("'" + child.getValue() + "' node must not be defined outside a defs Section");
					continue;
				}
				elementParser = new LinearGradient(this.paint);
			} else if (child.getValue().equals("defs")) {
				if (isReference) {
					LOGGER.error("'" + child.getValue() + "' node must not be defined in a defs Section");
					continue;
				}
				final boolean retRefs = parseXMLData(child, true);
				// TODO Use retRefs ...
				continue;
			} else if (child.getValue().equals("sodipodi:namedview")) {
				// Node ignore : generaly inkscape data
				continue;
			} else if (child.getValue().equals("metadata")) {
				// Node ignore : generaly inkscape data
				continue;
			} else {
				LOGGER.error("node not suported : '" + child.getValue()
						+ "' must be [title,g,a,path,rect,circle,ellipse,line,polyline,polygon,text,metadata]");
			}
			if (elementParser == null) {
				LOGGER.error("error on node: '" + child.getValue() + "' allocation error or not supported ...");
				continue;
			}
			if (!elementParser.parseXML(child, this.transformMatrix, size)) {
				LOGGER.error("error on node: '" + child.getValue() + "' Sub Parsing ERROR");
				elementParser = null;
				continue;
			}
			if (maxSize.x() < size.value.x()) {
				maxSize = maxSize.withX(size.value.x());
			}
			if (maxSize.y() < size.value.y()) {
				maxSize = maxSize.withY(size.value.y());
			}
			// add element in the system
			if (!isReference) {
				this.subElementList.add(elementParser);
			} else {
				this.refList.add(elementParser);
			}
		}
		if (this.size.x() == 0 || this.size.y() == 0) {
			this.size = Vector2f.clipInt(maxSize);
		} else {
			this.size = Vector2f.clipInt(this.size);
		}
		if (!isReference) {
			displayDebug();
		}
		return true;
	}

	/*
	public float[][] renderImageFloat(final Vector2i size) {
		return renderImageFloat(size, false);
	}

	public float[][] renderImageFloat(Vector2i size, final boolean visualDebug) {
		if (size == null) {
			size = new Vector2i((int) this.size.x(), (int) this.size.y());
		} else {
			if (size.x() <= 0) {
				size = size.withX((int) this.size.x());
			}
			if (size.y() <= 0) {
				size = size.withY((int) this.size.y());
			}
		}
		LOGGER.debug("Generate size " + size);
		Renderer renderedElement = new Renderer(size, this, visualDebug);
		// create the first element matrix modification ...
		Matrix2x3f basicTrans = Matrix2x3f.IDENTITY.multiply(Matrix2x3f.createScale(new Vector2f(size.x() / this.size.x(), size.y() / this.size.y())));
		draw(renderedElement, basicTrans);

		// direct return the generated data ...
		return renderedElement.getData();
	}
	*/
	/**
	 * Generate Image in a specific format.
	 * @param size Size expected of the rendered image (value <=0 if it need to be automatic.) return the size generate
	 * @return Vector of the data used to display (simple vector: generic to transmit)
	 */
	public ImageFloatRGBA renderImageFloatRGBA(final Vector2i size) {
		return renderImageFloatRGBA(size, false);
	}

	public ImageFloatRGBA renderImageFloatRGBA(Vector2i size, final boolean visualDebug) {
		if (size == null) {
			size = new Vector2i((int) this.size.x(), (int) this.size.y());
		} else {
			if (size.x() <= 0) {
				size = size.withX((int) Math.abs(this.size.x()));
			}
			if (size.y() <= 0) {
				size = size.withY((int) Math.abs(this.size.y()));
			}
		}
		if (size.x() <= 0) {
			LOGGER.error("Generate size " + size);
		}
		if (size.y() <= 0) {
			LOGGER.error("Generate size " + size);
		}
		LOGGER.trace("Generate size " + size);
		final Renderer renderedElement = new Renderer(size, this, visualDebug);
		// create the first element matrix modification ...
		final Matrix2x3f basicTrans = Matrix2x3f.IDENTITY
				.multiply(Matrix2x3f.createScale(new Vector2f(size.x() / this.size.x(), size.y() / this.size.y())));
		draw(renderedElement, basicTrans);

		// direct return the generated data ...
		return renderedElement.getData();
	}

}

package org.atriasoft.esvg;

import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.render.SvgRenderBuffer;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.esvg.internal.XmlHelper;
import org.w3c.dom.Element;
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
	private static final boolean envDisplayRefs = "true".equals(System.getenv("ESQG_DISPLAY_REFS"));

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
	public boolean cleanStyleProperty(final Element root) {
		// for each nodes:
		for (final Element child : XmlHelper.children(root)) {
			// get attribute style:
			if (child.hasAttribute("style")) {
				final String content = XmlHelper.attr(child, "style", "");
				if (content.length() != 0) {
					final String[] listStyle = content.split(";");
					for (final String it1 : listStyle) {
						final String[] value = it1.split(":");
						if (value.length != 2) {
							LOGGER.warn("parsing style with a wrong patern : {} missing ':'", it1);
							continue;
						}
						// TODO Check if the attibute already exist ...
						child.setAttribute(value[0].trim(), value[1].trim());
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
		LOGGER.debug("Main SVG: size={}", this.size);
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
		LOGGER.trace("{}DRAW shape EsvgDocument", spacingDist(level));
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
		LOGGER.debug("lineification size {}", size);
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
		LOGGER.warn("Can not find reference name : '{}'", name);
		return null;
	}

	public boolean isLoadOk() {
		return this.loadOK;
	}

	/**
	 * Load the file that might contain the svg
	 * @param uri File of the svg
	 * @return false : An error occured
	 * @return true : Parsing is OK
	 */
	public boolean load(final Uri uri) {
		clear();
		this.uri = uri;
		Element doc = null;
		try (final java.io.InputStream is = Uri.getStream(uri)) {
			if (is == null) {
				LOGGER.error("Can not read the Stream : {}", uri);
				return false;
			}
			doc = XmlHelper.parse(is);
		} catch (final Exception e) {
			LOGGER.error("Failed to load SVG from URI: {}", uri, e);
			return false;
		}
		return parseXML(doc);
	}

	/**
	 * parse a string that contain an svg stream
	 * @param data Data to parse
	 * @return false : An error occured
	 * @return true : Parsing is OK
	 */
	public boolean parse(final String data) {
		clear();
		Element doc = null;
		try {
			doc = XmlHelper.parse(data);
		} catch (final Exception e) {
			LOGGER.error("Failed to parse SVG data", e);
			return false;
		}
		return parseXML(doc);
	}
	
	public boolean parseXML(final Element doc) {
		if (doc == null) {
			return false;
		}
		// If the root element is already <svg>, use it directly
		if ("svg".equals(doc.getTagName())) {
			cleanStyleProperty(doc);
			this.loadOK = parseXMLData(doc);
		} else {
			// Otherwise look for <svg> as a child
			final Element svgElement = XmlHelper.getNode(doc, "svg");
			if (svgElement != null) {
				cleanStyleProperty(svgElement);
				this.loadOK = parseXMLData(svgElement);
			}
		}
		return this.loadOK;
	}
	
	public boolean parseXMLData(final Element root) {
		return parseXMLData(root, false);
	}

	public boolean parseXMLData(final Element root, final boolean isReference) {
		// get the svg version :
		this.version = XmlHelper.attr(root, "version", "");
		// parse ...
		Vector2f pos = Vector2f.ZERO;
		if (!isReference) {
			parseTransform(root);
			pos = parseXmlPosition(root);
			this.size = parseXmlSize(root);
			// If width/height are not defined, try to deduce size from viewBox
			if (this.size.x() == 0 || this.size.y() == 0) {
				final String viewBox = XmlHelper.attr(root, "viewBox", "");
				if (!viewBox.isEmpty()) {
					// viewBox format: "minX minY width height" (can use space or comma as separator)
					final String[] parts = viewBox.trim().split("[\\s,]+");
					if (parts.length == 4) {
						try {
							final float viewBoxWidth = Float.parseFloat(parts[2]);
							final float viewBoxHeight = Float.parseFloat(parts[3]);
							if (this.size.x() == 0) {
								this.size = this.size.withX(viewBoxWidth);
							}
							if (this.size.y() == 0) {
								this.size = this.size.withY(viewBoxHeight);
							}
							LOGGER.trace("Size deduced from viewBox: {}", this.size);
						} catch (final NumberFormatException e) {
							LOGGER.warn("Failed to parse viewBox values: '{}'", viewBox);
						}
					} else {
						LOGGER.warn("Invalid viewBox format (expected 4 values): '{}'", viewBox);
					}
				}
			}
			parsePaintAttr(root);
			LOGGER.trace("parsed .ROOT trans: {}", this.transformMatrix);
		} else {
			LOGGER.trace("Parse Reference section ... (no attibute)");
		}

		Vector2f maxSize = Vector2f.ZERO;
		final Dynamic<Vector2f> size = new Dynamic<>(Vector2f.ZERO);
		// parse all sub node:
		for (final Element child : XmlHelper.children(root)) {
			Base elementParser = null;
			if (child.getTagName().equals("g")) {
				elementParser = new Group(this.paint);
			} else if (child.getTagName().equals("a")) {
				LOGGER.info("Note : 'a' balise is parsed like a g balise ...");
				elementParser = new Group(this.paint);
			} else if (child.getTagName().equals("title")) {
				this.title = "TODO : set the title here ...";
				continue;
			} else if (child.getTagName().equals("path")) {
				elementParser = new Path(this.paint);
			} else if (child.getTagName().equals("rect")) {
				elementParser = new Rectangle(this.paint);
			} else if (child.getTagName().equals("circle")) {
				elementParser = new Circle(this.paint);
			} else if (child.getTagName().equals("ellipse")) {
				elementParser = new Ellipse(this.paint);
			} else if (child.getTagName().equals("line")) {
				elementParser = new Line(this.paint);
			} else if (child.getTagName().equals("polyline")) {
				elementParser = new Polyline(this.paint);
			} else if (child.getTagName().equals("polygon")) {
				elementParser = new Polygon(this.paint);
			} else if (child.getTagName().equals("text")) {
				elementParser = new Text(this.paint);
			} else if (child.getTagName().equals("radialGradient")) {
				if (!isReference) {
					LOGGER.warn("'{}' node must not be defined outside a defs Section", child.getTagName());
					continue;
				}
				elementParser = new RadialGradient(this.paint);
			} else if (child.getTagName().equals("linearGradient")) {
				if (!isReference) {
					LOGGER.warn("'{}' node must not be defined outside a defs Section", child.getTagName());
					continue;
				}
				elementParser = new LinearGradient(this.paint);
			} else if (child.getTagName().equals("defs")) {
				if (isReference) {
					LOGGER.warn("'{}' node must not be defined in a defs Section", child.getTagName());
					continue;
				}
				final boolean retRefs = parseXMLData(child, true);
				// TODO Use retRefs ...
				continue;
			} else if (child.getTagName().equals("sodipodi:namedview")) {
				// Node ignore : generaly inkscape data
				continue;
			} else if (child.getTagName().equals("metadata")) {
				// Node ignore : generaly inkscape data
				continue;
			} else {
				LOGGER.warn(
						"node not suported : '{}' must be [title,g,a,path,rect,circle,ellipse,line,polyline,polygon,text,metadata]",
						child.getTagName());
			}
			if (elementParser == null) {
				LOGGER.warn("error on node: '{}' allocation error or not supported ...", child.getTagName());
				continue;
			}
			if (!elementParser.parseXML(child, this.transformMatrix, size)) {
				LOGGER.warn("error on node: '{}' Sub Parsing ERROR", child.getTagName());
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
		if (envDisplayRefs && !isReference) {
			displayDebug();
		}
		return true;
	}

	/**
	 * Render the SVG to a standard Java {@link BufferedImage}.
	 * @param size Size expected of the rendered image (value <=0 if it need to be automatic.)
	 * @return The rendered image as a BufferedImage (TYPE_INT_ARGB)
	 */
	public BufferedImage renderImage(final Vector2i size) {
		return renderImage(size, false);
	}

	public BufferedImage renderImage(Vector2i size, final boolean visualDebug) {
		return renderSvgBuffer(size, visualDebug).toBufferedImage();
	}

	/**
	 * Render the SVG to an internal float RGBA buffer.
	 * Useful for tests that need float-precision pixel access.
	 * @param size Size expected of the rendered image (value <=0 if it need to be automatic.)
	 * @return The rendered buffer with float RGBA data
	 */
	public SvgRenderBuffer renderSvgBuffer(final Vector2i size) {
		return renderSvgBuffer(size, false);
	}

	public SvgRenderBuffer renderSvgBuffer(Vector2i size, final boolean visualDebug) {
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
			LOGGER.warn("Generate size X is invalid: {}", size);
		}
		if (size.y() <= 0) {
			LOGGER.warn("Generate size Y is invalid: {}", size);
		}
		LOGGER.trace("Generate size {}", size);
		final Renderer renderedElement = new Renderer(size, this, visualDebug);
		// create the first element matrix modification ...
		final Matrix2x3f basicTrans = Matrix2x3f.IDENTITY
				.multiply(Matrix2x3f.createScale(new Vector2f(size.x() / this.size.x(), size.y() / this.size.y())));
		draw(renderedElement, basicTrans);

		// direct return the generated data ...
		return renderedElement.getData();
	}

}

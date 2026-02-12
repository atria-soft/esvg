package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.etk.Color;
import org.atriasoft.etk.Dimension1f;
import org.atriasoft.etk.Dimension2f;
import org.atriasoft.etk.Distance;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.esvg.internal.XmlHelper;
import org.w3c.dom.Element;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class RadialGradient extends Base {
	static final Logger LOGGER = LoggerFactory.getLogger(RadialGradient.class);
	private Dimension2f center = new Dimension2f(new Vector2f(50, 50), Distance.POURCENT); //!< gradient position cx cy
	private final List<Pair<Float, Color>> data = new ArrayList<>(); //!< incompatible with href
	private Dimension2f focal = new Dimension2f(new Vector2f(50, 50), Distance.POURCENT); //!< gradient Focal fx fy
	private String href = ""; //!< in case of using a single gradient in multiple gradient, the gradient is store in an other element...
	private Dimension1f radius = new Dimension1f(50, Distance.POURCENT); //!< Radius of the gradient
	public SpreadMethod spread = SpreadMethod.PAD;
	public GradientUnits unit = GradientUnits.GRADIENT_UNITS_OBJECT_BOUNDING_BOX;

	public RadialGradient(final PaintState parentPaintState) {
		super(parentPaintState);
	}

	@Override
	public void display(final int spacing) {
		LOGGER.debug("{}RadialGradient center={} focal={} radius={}", spacingDist(spacing), this.center, this.focal, this.radius);
		for (final Pair<Float, Color> it : this.data) {
			LOGGER.debug("{}STOP: offset={} color={}", spacingDist(spacing + 1), it.first, it.second);
		}
	}

	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		LOGGER.trace("{}DRAW esvg::RadialGradient", spacingDist(level));
	}

	public Dimension2f getCenter() {
		return this.center;
	}

	public List<Pair<Float, Color>> getColors(final EsvgDocument document) {
		if (this.href.isEmpty()) {
			return this.data;
		}
		if (document == null) {
			LOGGER.error("Get null input for document");
			return this.data;
		}
		final Base base = document.getReference(this.href);
		if (base == null) {
			LOGGER.error("Can not get base : '{}'", this.href);
			return this.data;
		}
		if (base instanceof final RadialGradient gradientR) {
			return gradientR.getColors(document);
		}
		if (base instanceof final LinearGradient gradientL) {
			return gradientL.getColors(document);
		}
		return this.data;
	}

	public Dimension2f getFocal() {
		return this.focal;
	}

	public Dimension1f getRadius() {
		return this.radius;
	}

	@Override
	public boolean parseXML(final Element element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		// line must have a minimum size...
		//this.paint.strokeWidth = 1;
		if (element == null) {
			return false;
		}

		// ---------------- get unique ID ----------------
		this.id = XmlHelper.attr(element, "id", "");

		//parseTransform(element);
		//parsePaintAttr(element);

		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);

		String contentX = XmlHelper.attr(element, "cx", "");
		String contentY = XmlHelper.attr(element, "cy", "");
		if (!contentX.isEmpty() && !contentY.isEmpty()) {
			this.center = Dimension2f.valueOf(contentX, contentY);
		}
		contentX = XmlHelper.attr(element, "r", "");
		if (contentX != "") {
			this.radius = Dimension1f.valueOf(contentX);
		}
		contentX = XmlHelper.attr(element, "fx", "");
		contentY = XmlHelper.attr(element, "fy", "");
		if (!contentX.isEmpty() && !contentY.isEmpty()) {
			this.focal = Dimension2f.valueOf(contentX, contentY);
		}
		contentX = XmlHelper.attr(element, "gradientUnits", "");
		if (contentX.equals("userSpaceOnUse")) {
			this.unit = GradientUnits.GRADIENT_UNITS_USER_SPACE_ON_USE;
		} else {
			this.unit = GradientUnits.GRADIENT_UNITS_OBJECT_BOUNDING_BOX;
			if (contentX.length() != 0 && contentX != "objectBoundingBox") {
				LOGGER.warn("Parsing error of 'gradientUnits' ==> not suported value: '{}' not in : {{userSpaceOnUse/objectBoundingBox}} use objectBoundingBox", contentX);
			}
		}
		contentX = XmlHelper.attr(element, "spreadMethod", "");
		if (contentX.equals("reflect")) {
			this.spread = SpreadMethod.REFLECT;
		} else if (contentX.equals("repeat")) {
			this.spread = SpreadMethod.REPEAT;
		} else {
			this.spread = SpreadMethod.PAD;
			if (contentX.length() != 0 && !contentX.equals("pad")) {
				LOGGER.warn("Parsing error of 'spreadMethod' ==> not suported value: '{}' not in : {{reflect/repeate/pad}} use pad", contentX);
			}
		}
		// note: xlink:href is incompatible with subNode "stop"
		this.href = XmlHelper.attr(element, "xlink:href", "");
		if (this.href.length() != 0) {
			this.href = this.href.substring(1);
		}
		// parse all sub node :
		for (final Element child : XmlHelper.children(element)) {
			if (child.getTagName().equals("stop")) {
				float offset = 100;
				Color stopColor = Color.NONE;
				String content = XmlHelper.attr(child, "offset", "");
				if (content.length() != 0) {
					final Pair<Float, Distance> tmp = parseLength2(content);
					if (tmp.second == Distance.PIXEL) {
						// special case ==> all time % then no type define ==> % in [0.0 .. 1.0]
						offset = tmp.first * 100.0f;
					} else if (tmp.second != Distance.POURCENT) {
						LOGGER.warn("offset : {} res={},{} Not support other than pourcent %", content, tmp.first, tmp.second);
					} else {
						offset = tmp.first;
					}
				}
				content = XmlHelper.attr(child, "stop-color", "");
				if (content.length() != 0) {
					stopColor = parseColor(content).first;
					LOGGER.trace(" color : \"{}\"  == > {}", content, stopColor);
				}
				content = XmlHelper.attr(child, "stop-opacity", "");
				if (content.length() != 0) {
					float opacity = parseLength(content);
					opacity = FMath.avg(0.0f, opacity, 1.0f);
					stopColor = stopColor.withA(opacity);
					LOGGER.trace(" opacity : '{}'  == > {}", content, stopColor);
				}
				this.data.add(new Pair<>(offset, stopColor));
			} else {
				LOGGER.warn("node not suported : '{}' must be [stop]", child.getTagName());
			}
		}
		if (this.data.size() != 0) {
			if (!this.href.isEmpty()) {
				LOGGER.warn("node can not have an xlink:href element with sub node named: stop ==> removing href");
				this.href = "";
			}
		}
		return true;
	}

}

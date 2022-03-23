package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Dimension2f;
import org.atriasoft.etk.Distance;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.exml.model.XmlElement;
import org.atriasoft.exml.model.XmlNode;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class LinearGradient extends Base {
	private final List<Pair<Float, Color>> data = new ArrayList<>(); //!< gradient position x1 y1
	private String href = ""; //!< gradient position x2 y2
	private Dimension2f pos1 = new Dimension2f(new Vector2f(50, 50), Distance.POURCENT);
	private Dimension2f pos2 = new Dimension2f(new Vector2f(50, 50), Distance.POURCENT);
	
	public SpreadMethod spread = SpreadMethod.PAD; //!< in case of using a single gradient in multiple gradient, the gradient is store in an other element...
	
	public GradientUnits unit = GradientUnits.GRADIENT_UNITS_OBJECT_BOUNDING_BOX; //!< incompatible with href
	
	public LinearGradient(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	@Override
	public void display(final int spacing) {
		
		Log.debug(spacingDist(spacing) + "LinearGradient " + this.pos1 + " to " + this.pos2);
		for (Pair<Float, Color> it : this.data) {
			Log.debug(spacingDist(spacing + 1) + "STOP: offset=" + it.first + " color=" + it.second);
		}
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::LinearGradient");
	}
	
	public List<Pair<Float, Color>> getColors(final EsvgDocument document) {
		if (this.href.isEmpty()) {
			return this.data;
		}
		if (document == null) {
			Log.error("Get null input for document");
			return this.data;
		}
		Base base = document.getReference(this.href);
		if (base == null) {
			Log.error("Can not get base : '" + this.href + "'");
			return this.data;
		}
		if (base instanceof RadialGradient gradientR) {
			return gradientR.getColors(document);
		}
		if (base instanceof LinearGradient gradientL) {
			return gradientL.getColors(document);
		}
		return this.data;
	}
	
	public Dimension2f getPosition1() {
		return this.pos1;
	}
	
	public Dimension2f getPosition2() {
		return this.pos2;
	}
	
	@Override
	public boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		{
			// line must have a minimum size...
			//this.paint.strokeWidth = 1;
			if (element == null) {
				return false;
			}
			
			// ---------------- get unique ID ----------------
			this.id = element.getAttribute("id", "");
			
			//parseTransform(element);
			//parsePaintAttr(element);
			
			// add the property of the parrent modifications ...
			this.transformMatrix = this.transformMatrix.multiply(parentTrans);
			
			String contentX = element.getAttribute("x1", "");
			String contentY = element.getAttribute("y1", "");
			if (!contentX.isEmpty() && !contentY.isEmpty()) {
				this.pos1 = Dimension2f.valueOf(contentX, contentY);
			}
			contentX = element.getAttribute("x2", "");
			contentY = element.getAttribute("y2", "");
			if (!contentX.isEmpty() && !contentY.isEmpty()) {
				this.pos2 = Dimension2f.valueOf(contentX, contentY);
			}
			contentX = element.getAttribute("gradientUnits", "");
			if (contentX.equals("userSpaceOnUse")) {
				this.unit = GradientUnits.GRADIENT_UNITS_USER_SPACE_ON_USE;
			} else {
				this.unit = GradientUnits.GRADIENT_UNITS_OBJECT_BOUNDING_BOX;
				if (contentX.length() != 0 && contentX != "objectBoundingBox") {
					Log.error("Parsing error of 'gradientUnits' ==> not suported value: '" + contentX + "' not in : {userSpaceOnUse/objectBoundingBox} use objectBoundingBox");
				}
			}
			contentX = element.getAttribute("spreadMethod", "");
			if (contentX.equals("reflect")) {
				this.spread = SpreadMethod.REFLECT;
			} else if (contentX.equals("repeat")) {
				this.spread = SpreadMethod.REPEAT;
			} else {
				this.spread = SpreadMethod.PAD;
				if (contentX.length() != 0 && !contentX.equals("pad")) {
					Log.error("Parsing error of 'spreadMethod' ==> not suported value: '" + contentX + "' not in : {reflect/repeate/pad} use pad");
				}
			}
			// note: xlink:href is incompatible with subNode "stop"
			this.href = element.getAttribute("xlink:href", "");
			if (this.href.length() != 0) {
				this.href = this.href.substring(1);
			}
			// parse all sub node :
			for (XmlNode it : element.getNodes()) {
				if (it instanceof XmlElement child) {
					if (child.getValue().equals("stop")) {
						float offset = 100;
						Color stopColor = Color.NONE;
						String content = child.getAttribute("offset", "");
						if (content.length() != 0) {
							Pair<Float, Distance> tmp = parseLength2(content);
							if (tmp.second == Distance.PIXEL) {
								// special case ==> all time % then no type define ==> % in [0.0 .. 1.0]
								offset = tmp.first * 100.0f;
							} else if (tmp.second != Distance.POURCENT) {
								Log.error("offset : " + content + " res=" + tmp.first + "," + tmp.second + " Not support other than pourcent %");
							} else {
								offset = tmp.first;
							}
						}
						content = child.getAttribute("stop-color", "");
						if (content.length() != 0) {
							stopColor = parseColor(content).first;
							Log.verbose(" color : '" + content + "' == > " + stopColor);
						}
						content = child.getAttribute("stop-opacity", "");
						if (content.length() != 0) {
							float opacity = parseLength(content);
							opacity = FMath.avg(0.0f, opacity, 1.0f);
							stopColor = stopColor.withA(opacity);
							Log.verbose(" opacity : '" + content + "'  == > " + stopColor);
						}
						this.data.add(new Pair<>(offset, stopColor));
					} else {
						Log.error(" node not suported : '" + child.getValue() + "' must be [stop]");
					}
				}
			}
			if (this.data.size() != 0) {
				if (!this.href.isEmpty()) {
					Log.error(" node can not have an xlink:href element with sub node named: stop ==> removing href");
					this.href = "";
				}
			}
			return true;
		}
		
	}
}

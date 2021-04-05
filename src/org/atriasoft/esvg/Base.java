package org.atriasoft.esvg;

import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Distance;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.exml.model.XmlElement;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Base {
	
	public static float kappa90 = 0.5522847493f; //!< proportional lenght to the radius of a bezier handle for 90° arcs.
	
	private static String extractTransformData(final String value, final String base) {
		int posStart = value.indexOf(base);
		if (posStart == -1) {
			// Not indexOf element is a normal case ...
			return "";
		}
		posStart += base.length();
		if (value.length() < posStart + 2) {
			Log.error("Not enought spece in the String to have transform value for ' (' or '()' in '" + value + "'");
			return "";
		}
		if (value.charAt(posStart) == '(') {
			// normal SVG does not support this case ...
			posStart++;
		} else if (value.charAt(posStart) == ' ' && value.charAt(posStart + 1) == '(') {
			posStart += 2;
		} else {
			Log.error("Can not indexOf ' (' or '(' in '" + value.substring(posStart) + "' for '" + value + "'");
			return "";
		}
		if (value.length() < posStart + 1) {
			Log.error("Not enought spece in the String to have transform value for ')' in '" + value + "'");
			return "";
		}
		int posEnd = value.indexOf(')', posStart);
		if (posEnd == -1) {
			Log.error("Missing element ')' in '" + value + "' for " + base);
			return "";
		}
		Log.verbose("indexOf : '" + value.substring(posStart, posEnd) + "' for " + base);
		return value.substring(posStart, posEnd);
	}
	
	protected String id; //!< unique ID of the element.
	
	protected PaintState paint = new PaintState();
	
	protected Matrix2x3f transformMatrix = Matrix2x3f.IDENTITY; //!< specific render of the curent element
	
	public Base() {
		this.paint = new PaintState();
	}
	
	Base(final PaintState parentPaintState) {
		// copy the parent painting properties ...
		this.paint = parentPaintState.clone();
	}
	
	void display(final int spacing) {}
	
	void draw(final Renderer myRenderer, final Matrix2x3f basicTrans) {
		draw(myRenderer, basicTrans, 1);
	}
	
	/**
	 * Draw the form in the renderer
	 * @param myRenderer Renderer engine
	 * @param basicTrans Parant transformation of the environement
	 * @param level Level of the tree
	 */
	void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.warning(spacingDist(level) + "DRAW esvg::Base ... ==> No drawing availlable");
	}
	
	public void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans) {
		drawShapePoints(out, recurtionMax, threshold, basicTrans, 1);
	}
	
	/**
	 * Draw rhe shape with all points
	 * @param out where the lines are added
	 * @param recurtionMax interpolation recurtion max
	 * @param threshold threshold to stop recurtion
	 * @param basicTrans Parant transformation of the environement   
	 * @param level Level of the tree
	 */
	void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans, final int level) {
		
	}
	
	/**
	 * Get the ID of the Element
	 * @return UniqueId in the svg file
	 */
	public String getId() {
		return this.id;
	}
	
	/**
	 * parse a color specification from the svg file
	 * @param inputData Data C String with the xml definition
	 * @return The parsed color (color used and the link if needed)
	 */
	Pair<Color, String> parseColor(final String inputData) {
		Pair<Color, String> localColor = new Pair<>(Color.WHITE, "");
		if (inputData.length() > 4 && inputData.charAt(0) == 'u' && inputData.charAt(1) == 'r' && inputData.charAt(2) == 'l' && inputData.charAt(3) == '(') {
			if (inputData.charAt(4) == '#') {
				String color = inputData.substring(5, inputData.length() - 1);
				localColor = new Pair<>(Color.NONE, color);
			} else {
				Log.error("Problem in parsing the color : '" + inputData + "'  == > url(XXX) is not supported now ...");
			}
		} else {
			try {
				localColor = new Pair<>(Color.valueOf256(inputData), "");
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		Log.verbose("Parse color : \"" + inputData + "\"  == > " + localColor.first + " " + localColor.second);
		return localColor;
	}
	
	/**
	 * parse a lenght of the xml element
	 * @param dataInput Data C String with the printed lenght
	 * @return standard number of pixels
	 */
	float parseLength(final String dataInput) {
		Pair<Float, Distance> value = parseLength2(dataInput);
		Log.verbose(" lenght : '" + value.first + "' => unit=" + value.second);
		float fontsize = 20.0f;
		switch (value.second) {
			case POURCENT:
				return value.first;// / 100.0 * this.paint.viewPort.x();
			case ELEMENT:
				return value.first * fontsize;
			case EX:
				return value.first / 2.0f * fontsize;
			case PIXEL:
				return value.first;
			case POINT:
				return value.first * 1.25f;
			case PC:
				return value.first * 15.0f;
			case MILLIMETER:
				return value.first * 3.543307f;
			case CENTIMETER:
				return value.first * 35.43307f;
			case INCH:
				return value.first * 90.0f;
			default:
				return 0.0f;
		}
	}
	
	Pair<Float, Distance> parseLength2(String config) {
		
		Distance type = Distance.PIXEL;
		if (config.endsWith("%")) {
			type = Distance.POURCENT;
			config = config.substring(0, config.length() - 1);
		} else if (config.endsWith("px")) {
			type = Distance.PIXEL;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("ft")) {
			type = Distance.FOOT;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("in")) {
			type = Distance.INCH;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("km")) {
			type = Distance.KILOMETER;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("mm")) {
			type = Distance.MILLIMETER;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("cm")) {
			type = Distance.CENTIMETER;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("m")) {
			type = Distance.METER;
			config = config.substring(0, config.length() - 1);
		} else if (config.endsWith("em")) {
			type = Distance.ELEMENT;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("ex")) {
			type = Distance.EX;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("pt")) {
			type = Distance.POINT;
			config = config.substring(0, config.length() - 2);
		} else if (config.endsWith("pc")) {
			type = Distance.PC;
			config = config.substring(0, config.length() - 2);
		}
		final float tmp = Float.parseFloat(config);
		return new Pair<>(tmp, type);
	}
	
	/**
	 * parse a Painting attribute of a specific node
	 * @param element Basic node of the XML that might be parsed
	 */
	void parsePaintAttr(final XmlElement element) {
		if (element == null) {
			return;
		}
		/*
		boolean fillNone = false;
		boolean strokeNone = false;
		*/
		String content;
		// ---------------- get unique ID ----------------
		this.id = element.getAttribute("id", "");
		// ---------------- stroke ----------------
		content = element.getAttribute("stroke", "");
		if (content.equals("none")) {
			this.paint.stroke = new Pair<>(Color.NONE, "");
		} else {
			if (content.length() != 0) {
				this.paint.stroke = parseColor(content);
				Log.error("Parse color : " + this.paint.stroke);
			}
			content = element.getAttribute("stroke-width", "");
			if (content.length() != 0) {
				this.paint.strokeWidth = parseLength(content);
			}
			content = element.getAttribute("stroke-opacity", "");
			if (content.length() != 0) {
				float opacity = parseLength(content);
				opacity = FMath.avg(0.0f, opacity, 1.0f);
				this.paint.stroke = this.paint.stroke.withFirst(this.paint.stroke.first.withA(opacity));
			}
			
			content = element.getAttribute("stroke-dasharray", "");
			if (content.length() != 0) {
				if (content.equals("none")) {
					// OK, Nothing to do ...
				} else {
					Log.todo(" 'stroke-dasharray' not implemented ...");
				}
			}
			content = element.getAttribute("stroke-linecap", "");
			if (content.length() != 0) {
				if (content.equals("butt")) {
					this.paint.lineCap = CapMode.BUTT;
				} else if (content.equals("round")) {
					this.paint.lineCap = CapMode.ROUND;
				} else if (content.equals("square")) {
					this.paint.lineCap = CapMode.SQUARE;
				} else {
					this.paint.lineCap = CapMode.BUTT;
					Log.error("not know stroke-linecap value : '" + content + "', not in [butt,round,square]");
				}
			}
			content = element.getAttribute("stroke-linejoin", "");
			if (content.length() != 0) {
				if (content.equals("miter")) {
					this.paint.lineJoin = JoinMode.MITER;
				} else if (content.equals("round")) {
					this.paint.lineJoin = JoinMode.ROUND;
				} else if (content.equals("bevel")) {
					this.paint.lineJoin = JoinMode.BEVEL;
				} else {
					this.paint.lineJoin = JoinMode.MITER;
					Log.error("not know stroke-linejoin value : '" + content + "', not in [miter,round,bevel]");
				}
			}
			content = element.getAttribute("stroke-miterlimit", "");
			if (content.length() != 0) {
				float tmp = parseLength(content);
				this.paint.miterLimit = FMath.max(0.0f, tmp);
			}
		}
		// ---------------- FILL ----------------
		content = element.getAttribute("fill", "");
		if (content.equals("none")) {
			this.paint.fill = new Pair<>(Color.NONE, "");
		} else {
			if (content.length() != 0) {
				this.paint.fill = parseColor(content);
			}
			content = element.getAttribute("fill-opacity", "");
			if (content.length() != 0) {
				float opacity = parseLength(content);
				opacity = FMath.avg(0.0f, opacity, 1.0f);
				this.paint.fill = this.paint.fill.withFirst(this.paint.fill.first.withA(opacity));
			}
			content = element.getAttribute("fill-rule", "");
			if (content.length() != 0) {
				if (content.equals("nonzero")) {
					this.paint.flagEvenOdd = false;
				} else if (content.equals("evenodd")) {
					this.paint.flagEvenOdd = true;
				} else {
					Log.error("not know fill-rule value : \"" + content + "\", not in [nonzero,evenodd]");
				}
			}
			// ---------------- opacity ----------------
			content = element.getAttribute("opacity", "");
			if (content.length() != 0) {
				this.paint.opacity = parseLength(content);
				this.paint.opacity = FMath.avg(0.0f, this.paint.opacity, 1.0f);
			}
		}
	}
	
	protected void parseTransform(final XmlElement element) {
		if (element == null) {
			return;
		}
		String inputString = element.getAttribute("transform", "");
		if (inputString.length() == 0) {
			return;
		}
		Log.verbose("indexOf transform : '" + inputString + "'");
		inputString = inputString.replace(',', ' ');
		Log.verbose("indexOf transform : '" + inputString + "'");
		// need to indexOf elements in order ...
		String data = Base.extractTransformData(inputString, "matrix");
		if (data.length() != 0) {
			double[] matrix = FMath.getTableDouble(data, " ", 6);
			if (matrix != null) {
				this.transformMatrix = new Matrix2x3f(matrix);
				// indexOf a matrix : simply exit ...
				return;
			}
			Log.error("Parsing matrix() with wrong data ... '" + data + "'");
		}
		data = Base.extractTransformData(inputString, "translate");
		if (data.length() != 0) {
			float[] elements = FMath.getTableFloat(data, " ", 2);
			if (elements != null) {
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createTranslate(new Vector2f(elements[0], elements[1])));
				Log.verbose("Translate : " + elements[0] + ", " + elements[1]);
			} else {
				float elem = Float.parseFloat(data);
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createTranslate(new Vector2f(elem, 0)));
			}
		}
		data = Base.extractTransformData(inputString, "scale");
		if (data.length() != 0) {
			float[] elements = FMath.getTableFloat(data, " ", 2);
			if (elements != null) {
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createScale(new Vector2f(elements[0], elements[1])));
				Log.verbose("Translate : " + elements[0] + ", " + elements[1]);
			} else {
				float elem = Float.parseFloat(data);
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createScale(elem));
			}
		}
		data = Base.extractTransformData(inputString, "rotate");
		if (data.length() != 0) {
			float[] elements = FMath.getTableFloat(data, " ", 3);
			if (elements != null) {
				float angle = elements[0] / 180 * FMath.PI;
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createTranslate(new Vector2f(-elements[1], -elements[2])));
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createRotate(angle));
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createTranslate(new Vector2f(elements[1], elements[2])));
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createScale(new Vector2f(elements[0], elements[1])));
			} else {
				float elem = Float.parseFloat(data);
				float angle = elem / 180 * FMath.PI;
				Log.verbose("rotate : " + angle + "rad, " + (angle / FMath.PI * 180) + "0");
				this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createRotate(elem));
			}
		}
		data = Base.extractTransformData(inputString, "skewX");
		if (data.length() != 0) {
			float angle = Float.parseFloat(data);
			angle = angle / 180 * FMath.PI;
			Log.verbose("skewX : " + angle + "rad, " + (angle / FMath.PI * 180) + "0");
			this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createSkew(new Vector2f(angle, 0.0f)));
		}
		data = Base.extractTransformData(inputString, "skewY");
		if (data.length() != 0) {
			float angle = Float.parseFloat(data);
			angle = angle / 180 * FMath.PI;
			Log.verbose("skewY : " + angle + "rad, " + (angle / FMath.PI * 180) + "0");
			this.transformMatrix = this.transformMatrix.multiply(Matrix2x3f.createSkew(new Vector2f(0.0f, angle)));
		}
	}
	
	/**
	 * parse all the element needed in the basic node
	 * @param element standart XML node
	 * @return true if no problem arrived
	 */
	boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		// TODO UNDERSTAND why nothing is done here ...
		// Parse basic elements (ID...):
		this.id = element.getAttribute("id", "");
		sizeMax.value = Vector2f.ZERO;
		return false;
	}
	
	/**
	 * parse x, y, width, height attribute of the xml node
	 * @param element XML node
	 * @param pos parsed position
	 * @param size parsed dimention
	 */
	protected Vector2f parseXmlPosition(final XmlElement element) {
		Vector2f out = Vector2f.ZERO;
		
		if (element == null) {
			return out;
		}
		String content = element.getAttribute("x", "");
		if (content.length() != 0) {
			out = out.withX(parseLength(content));
		}
		content = element.getAttribute("y", "");
		if (content.length() != 0) {
			out = out.withY(parseLength(content));
		}
		return out;
	}
	
	protected Vector2f parseXmlSize(final XmlElement element) {
		Vector2f out = Vector2f.ZERO;
		if (element == null) {
			return out;
		}
		String content = element.getAttribute("width", "");
		if (content.length() != 0) {
			out = out.withX(parseLength(content));
		}
		content = element.getAttribute("height", "");
		if (content.length() != 0) {
			out = out.withY(parseLength(content));
		}
		return out;
	}
	
	/**
	 * Set the ID of the Element
	 * @param newId New Id of the element
	 */
	public void setId(final String newId) {
		this.id = newId;
	}
	
	protected String spacingDist(final int spacing) {
		StringBuilder out = new StringBuilder();
		for (int iii = 0; iii < spacing; iii++) {
			out.append("   ");
		}
		return out.toString();
	}
}

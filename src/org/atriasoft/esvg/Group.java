package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.exml.model.XmlElement;
import org.atriasoft.exml.model.XmlNode;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Group extends Base {
	private final List<Base> subElementList = new ArrayList<>(); //!< sub elements ...
	
	public Group(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	@Override
	public void display(final int spacing) {
		Log.debug(spacingDist(spacing) + "Group (START) fill=" + this.paint.fill.first + "/" + this.paint.fill.second + " stroke=" + this.paint.stroke.first + "/" + this.paint.stroke.second
				+ " stroke-width=" + this.paint.strokeWidth);
		for (final Base it : this.subElementList) {
			if (it != null) {
				it.display(spacing + 1);
			}
		}
		Log.debug(spacingDist(spacing) + "Group (STOP)");
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::group");
		for (Base it : this.subElementList) {
			if (it != null) {
				it.draw(myRenderer, basicTrans, level + 1);
			}
		}
	}
	
	@Override
	public void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW shape esvg::group");
		for (Base it : this.subElementList) {
			if (it != null) {
				it.drawShapePoints(out, recurtionMax, threshold, basicTrans, level + 1);
			}
		}
	}
	
	@Override
	public boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		if (element == null) {
			return false;
		}
		// parse ...
		Vector2f pos = Vector2f.ZERO;
		Vector2f size = Vector2f.ZERO;
		parseTransform(element);
		pos = parseXmlPosition(element);
		size = parseXmlSize(element);
		parsePaintAttr(element);
		Log.verbose("parsed G1.   trans : " + this.transformMatrix);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		Log.verbose("parsed G2.   trans : " + this.transformMatrix);
		
		sizeMax.value = Vector2f.ZERO;
		Dynamic<Vector2f> tmpPos = new Dynamic<Vector2f>(Vector2f.ZERO);
		// parse all sub node :
		for (XmlNode it : element.getNodes()) {
			if (!(it instanceof XmlElement child)) {
				// can be a comment ...
				continue;
			}
			Base elementParser = null;
			if (child.getValue().equals("g")) {
				elementParser = new Group(this.paint);
			} else if (child.getValue().equals("a")) {
				// TODO ...
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
			} else {
				Log.error("node not suported : '" + child.getValue() + "' must be [g,a,path,rect,circle,ellipse,line,polyline,polygon,text]");
			}
			if (elementParser == null) {
				Log.error("error on node: '" + child.getValue() + "' allocation error or not supported ...");
				continue;
			}
			if (!elementParser.parseXML(child, this.transformMatrix, tmpPos)) {
				Log.error(" error on node: '" + child.getValue() + "' Sub Parsing ERROR");
				elementParser = null;
				continue;
			}
			sizeMax.value = Vector2f.max(sizeMax.value, tmpPos.value);
			// add element in the system
			this.subElementList.add(elementParser);
		}
		return true;
	}
}

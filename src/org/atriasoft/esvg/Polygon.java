package org.atriasoft.esvg;

import org.atriasoft.esvg.render.DynamicColor;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.esvg.render.Point;
import org.atriasoft.esvg.render.PointList;
import org.atriasoft.esvg.render.SegmentList;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.exml.model.XmlElement;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Polygon extends Base {
	private final List<Vector2f> listPoint = new ArrayList<>(); //!< list of all point of the polygone
	
	public Polygon(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	private PathModel createPath() {
		PathModel out = new PathModel();
		out.moveTo(false, this.listPoint.get(0));
		for (int iii = 1; iii < this.listPoint.size(); iii++) {
			out.lineTo(false, this.listPoint.get(iii));
		}
		out.close();
		return out;
	}
	
	@Override
	public void display(final int spacing) {
		Log.debug(spacingDist(spacing) + "Polygon nbPoint=" + this.listPoint.size());
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::Polygon");
		
		PathModel listElement = createPath();
		
		Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);
		
		PointList listPoints = new PointList();
		listPoints = listElement.generateListPoints(level, myRenderer.getInterpolationRecurtionMax(), myRenderer.getInterpolationThreshold());
		//listPoints.applyMatrix(mtx);
		SegmentList listSegmentFill = new SegmentList();
		SegmentList listSegmentStroke = new SegmentList();
		Weight tmpFill = new Weight();
		Weight tmpStroke = new Weight();
		DynamicColor colorFill = DynamicColor.createColor(this.paint.fill, mtx);
		DynamicColor colorStroke = null;
		if (this.paint.strokeWidth > 0.0f) {
			colorStroke = DynamicColor.createColor(this.paint.stroke, mtx);
		}
		// Check if we need to display background
		if (colorFill != null) {
			listSegmentFill.createSegmentList(listPoints);
			colorFill.setViewPort(listSegmentFill.getViewPort());
			listSegmentFill.applyMatrix(mtx);
			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			tmpFill.generate(myRenderer.getSize(), myRenderer.getNumberSubScanLine(), listSegmentFill);
		}
		// check if we need to display stroke:
		if (colorStroke != null) {
			listSegmentStroke.createSegmentListStroke(listPoints, this.paint.strokeWidth, this.paint.lineCap, this.paint.lineJoin, this.paint.miterLimit);
			colorStroke.setViewPort(listSegmentStroke.getViewPort());
			listSegmentStroke.applyMatrix(mtx);
			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			tmpStroke.generate(myRenderer.getSize(), myRenderer.getNumberSubScanLine(), listSegmentStroke);
		}
		// add on images:
		myRenderer.print(tmpFill, colorFill, tmpStroke, colorStroke, this.paint.opacity);
		//myRenderer.addDebugSegment(listSegmentFill);
		//myRenderer.addDebugSegment(listSegmentStroke);
	}
	
	@Override
	public void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW Shape esvg::Polygon");
		PathModel listElement = createPath();
		Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);
		PointList listPoints;
		listPoints = listElement.generateListPoints(level, recurtionMax, threshold);
		listPoints.applyMatrix(mtx);
		for (List<Point> it : listPoints.data) {
			List<Vector2f> listPoint = new ArrayList<>();
			for (Point itDot : it) {
				listPoint.add(itDot.pos);
			}
			out.add(listPoint);
		}
	}
	
	@Override
	public boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		if (element == null) {
			return false;
		}
		parseTransform(element);
		parsePaintAttr(element);
		
		Log.verbose("parsed P1.   trans: " + this.transformMatrix);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		Log.verbose("parsed P2.   trans: " + this.transformMatrix);
		
		String sss1 = element.getAttribute("points", "");
		if (sss1.length() == 0) {
			Log.error("(l "/*+element.Pos()*/ + ") polygon: missing points attribute");
			return false;
		}
		
		sizeMax.value = Vector2f.ZERO;
		Log.verbose("Parse polyline : '" + sss1 + "'");
		String[] elems = sss1.split(" ");
		for (String elem : elems) {
			Vector2f pos = Vector2f.valueOf(elem);
			this.listPoint.add(pos);
			sizeMax.value = Vector2f.max(sizeMax.value, pos);
		}
		return true;
	}
}

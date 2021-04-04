package org.atriasoft.esvg;

import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.exml.model.XmlElement;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.DynamicColor;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.esvg.render.Point;
import org.atriasoft.esvg.render.PointList;
import org.atriasoft.esvg.render.SegmentList;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Rectangle extends Base {
	private Vector2f position = Vector2f.ZERO; //!< position of the rectangle
	private Vector2f roundedCorner = Vector2f.ZERO; //!< property of the rounded corner
	private Vector2f size = Vector2f.ZERO; //!< size of the rectangle
	
	public Rectangle(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	private PathModel createPath() {
		PathModel out = new PathModel();
		out.clear();
		if (this.roundedCorner.x() == 0.0f || this.roundedCorner.y() == 0.0f) {
			out.moveTo(false, this.position);
			out.lineToH(true, this.size.x());
			out.lineToV(true, this.size.y());
			out.lineToH(true, -this.size.x());
		} else {
			// Rounded rectangle
			out.moveTo(false, this.position.add(this.roundedCorner.x(), 0.0f));
			out.lineToH(true, this.size.x() - this.roundedCorner.x() * 2.0f);
			out.curveTo(true, new Vector2f(this.roundedCorner.x() * Base.kappa90, 0.0f), new Vector2f(this.roundedCorner.x(), this.roundedCorner.y() * (1.0f - Base.kappa90)),
					new Vector2f(this.roundedCorner.x(), this.roundedCorner.y()));
			out.lineToV(true, this.size.y() - this.roundedCorner.y() * 2.0f);
			out.curveTo(true, new Vector2f(0.0f, this.roundedCorner.y() * Base.kappa90), new Vector2f(-this.roundedCorner.x() * (1.0f - Base.kappa90), this.roundedCorner.y()),
					new Vector2f(-this.roundedCorner.x(), this.roundedCorner.y()));
			out.lineToH(true, -(this.size.x() - this.roundedCorner.x() * 2.0f));
			out.curveTo(true, new Vector2f(-this.roundedCorner.x() * Base.kappa90, 0.0f), new Vector2f(-this.roundedCorner.x(), -this.roundedCorner.y() * (1.0f - Base.kappa90)),
					new Vector2f(-this.roundedCorner.x(), -this.roundedCorner.y()));
			out.lineToV(true, -(this.size.y() - this.roundedCorner.y() * 2.0f));
			out.curveTo(true, new Vector2f(0.0f, -this.roundedCorner.y() * Base.kappa90), new Vector2f(this.roundedCorner.x() * (1.0f - Base.kappa90), -this.roundedCorner.y()),
					new Vector2f(this.roundedCorner.x(), -this.roundedCorner.y()));
		}
		out.close();
		return out;
	}
	
	@Override
	public void display(final int spacing) {
		Log.debug(spacingDist(spacing) + "Rectangle : pos=" + this.position + " size=" + this.size + " corner=" + this.roundedCorner);
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::Rectangle: fill=" + this.paint.fill.first + "/" + this.paint.fill.second + " stroke=" + this.paint.stroke.first + "/" + this.paint.stroke.second);
		PathModel listElement = createPath();
		
		Matrix2x3f mtx = this.transformMatrix;
		mtx = mtx.multiply(basicTrans);
		listElement.display(2);
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
		//myRenderer.addDebugSegment(listSegmentStroke)
		
	}
	
	@Override
	public void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW Shape esvg::Rectangle");
		PathModel listElement = createPath();
		Matrix2x3f mtx = this.transformMatrix;
		mtx = mtx.multiply(basicTrans);
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
		this.position = Vector2f.ZERO;
		this.size = Vector2f.ZERO;
		this.roundedCorner = Vector2f.ZERO;
		
		parseTransform(element);
		parsePaintAttr(element);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		this.position = parseXmlPosition(element);
		this.size = parseXmlSize(element);
		
		String content = element.getAttribute("rx", "");
		if (content.length() != 0) {
			this.roundedCorner = this.roundedCorner.withX(parseLength(content));
		}
		content = element.getAttribute("ry", "");
		if (content.length() != 0) {
			this.roundedCorner = this.roundedCorner.withY(parseLength(content));
		}
		sizeMax.value = new Vector2f(this.position.x() + this.size.x() + this.paint.strokeWidth, this.position.y() + this.size.y() + this.paint.strokeWidth);
		return true;
	}
}

package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;
import org.atriasoft.esvg.internal.Log;
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

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Ellipse extends Base {
	private Vector2f c; //!< Center property of the ellipse
	private Vector2f r; //!< Radius property of the ellipse
	
	public Ellipse(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	PathModel createPath() {
		PathModel out = new PathModel();
		out.moveTo(false, this.c.add(this.r.x(), 0.0f));
		out.curveTo(false, this.c.add(this.r.x(), this.r.y() * Base.kappa90), this.c.add(this.r.x() * Base.kappa90, this.r.y()), this.c.add(0.0f, this.r.y()));
		out.curveTo(false, this.c.add(-this.r.x() * Base.kappa90, this.r.y()), this.c.add(-this.r.x(), this.r.y() * Base.kappa90), this.c.add(-this.r.x(), 0.0f));
		out.curveTo(false, this.c.add(-this.r.x(), -this.r.y() * Base.kappa90), this.c.add(-this.r.x() * Base.kappa90, -this.r.y()), this.c.add(0.0f, -this.r.y()));
		out.curveTo(false, this.c.add(this.r.x() * Base.kappa90, -this.r.y()), this.c.add(this.r.x(), -this.r.y() * Base.kappa90), this.c.add(this.r.x(), 0.0f));
		out.close();
		return out;
	}
	
	@Override
	public void display(final int spacing) {
		Log.debug(spacingDist(spacing) + "Ellipse c=" + this.c + " r=" + this.r);
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::Ellipse");
		if (this.r.x() <= 0.0f || this.r.y() <= 0.0f) {
			Log.verbose(spacingDist(level + 1) + "Too small radius" + this.r);
			return;
		}
		PathModel listElement = createPath();
		
		Matrix2x3f mtx = this.transformMatrix;
		mtx = mtx.multiply(basicTrans);
		
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
		Log.verbose(spacingDist(level) + "DRAW Shape esvg::Ellipse");
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
		parseTransform(element);
		parsePaintAttr(element);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		this.c = Vector2f.ZERO;
		this.r = Vector2f.ZERO;
		
		String content = element.getAttribute("cx", "");
		if (content.length() != 0) {
			this.c = this.c.withX(parseLength(content));
		}
		content = element.getAttribute("cy", "");
		if (content.length() != 0) {
			this.c = this.c.withY(parseLength(content));
		}
		content = element.getAttribute("rx", "");
		if (content.length() == 0) {
			Log.error("Ellipse \"rx\" is not present");
			return false;
		}
		this.r = this.r.withX(parseLength(content));
		content = element.getAttribute("ry", "");
		if (content.length() == 0) {
			Log.error("Ellipse \"ry\" is not present");
			return false;
		}
		this.r = this.r.withY(parseLength(content));
		sizeMax.value = new Vector2f(this.c.x() + this.r.x(), this.c.y() + this.r.y());
		
		return true;
	}
}

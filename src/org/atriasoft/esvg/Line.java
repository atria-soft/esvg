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
public class Line extends Base {
	private Vector2f startPos = Vector2f.ZERO; //!< Start line position
	private Vector2f stopPos = Vector2f.ZERO; //!< Stop line position
	
	public Line(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	public Line(final Vector2f startPos, final Vector2f stopPos, final PaintState parentPaintState) {
		super(parentPaintState);
		this.startPos = startPos;
		this.stopPos = stopPos;
	}
	
	private PathModel createPath() {
		PathModel out = new PathModel();
		out.clear();
		out.moveTo(false, this.startPos);
		out.lineTo(false, this.stopPos);
		out.stop();
		return out;
	}
	
	@Override
	public void display(final int spacing) {
		Log.debug(spacingDist(spacing) + "Line " + this.startPos + " to " + this.stopPos);
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::Line");
		
		PathModel listElement = createPath();
		
		Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);
		
		PointList listPoints = new PointList();
		listPoints = listElement.generateListPoints(level, myRenderer.getInterpolationRecurtionMax(), myRenderer.getInterpolationThreshold());
		SegmentList listSegmentStroke = new SegmentList();
		Weight tmpFill = new Weight();
		Weight tmpStroke = new Weight();
		DynamicColor colorFill = DynamicColor.createColor(this.paint.fill, mtx);
		DynamicColor colorStroke = null;
		if (this.paint.strokeWidth > 0.0f) {
			colorStroke = DynamicColor.createColor(this.paint.stroke, mtx);
		}
		// Check if we need to display background
		// No background ...
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
	}
	
	@Override
	public void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW Shape esvg::Line");
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
		// line must have a minimum size...
		this.paint.strokeWidth = 1;
		if (element == null) {
			return false;
		}
		parseTransform(element);
		parsePaintAttr(element);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		String content = element.getAttribute("x1", "");
		if (content.length() != 0) {
			this.startPos = this.startPos.withX(parseLength(content));
		}
		content = element.getAttribute("y1", "");
		if (content.length() != 0) {
			this.startPos = this.startPos.withY(parseLength(content));
		}
		content = element.getAttribute("x2", "");
		if (content.length() != 0) {
			this.stopPos = this.stopPos.withX(parseLength(content));
		}
		content = element.getAttribute("y2", "");
		if (content.length() != 0) {
			this.stopPos = this.stopPos.withY(parseLength(content));
		}
		sizeMax.value = Vector2f.max(this.startPos, this.stopPos);
		return true;
	}
}

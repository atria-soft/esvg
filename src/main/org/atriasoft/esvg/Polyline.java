package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

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
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Polyline extends Base {
	static final Logger LOGGER = LoggerFactory.getLogger(Polyline.class);
	private final List<Vector2f> listPoint = new ArrayList<>(); //!< list of all point of the polyline

	public Polyline(final PaintState parentPaintState) {
		super(parentPaintState);
	}

	private PathModel createPath() {
		final PathModel out = new PathModel();
		out.clear();
		out.moveTo(false, this.listPoint.get(0));
		for (int iii = 1; iii < this.listPoint.size(); iii++) {
			out.lineTo(false, this.listPoint.get(iii));
		}
		out.stop();
		return out;
	}

	@Override
	public void display(final int spacing) {
		LOGGER.debug("{}Polyline nbPoint={}", spacingDist(spacing), this.listPoint.size());
	}

	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		LOGGER.trace("{}DRAW esvg::Polyline", spacingDist(level));

		final PathModel listElement = createPath();

		final Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);

		PointList listPoints;
		listPoints = listElement.generateListPoints(level, myRenderer.getInterpolationRecurtionMax(),
				myRenderer.getInterpolationThreshold());
		//listPoints.applyMatrix(mtx);
		final SegmentList listSegmentFill = new SegmentList();
		final SegmentList listSegmentStroke = new SegmentList();
		final Weight tmpFill = new Weight();
		final Weight tmpStroke = new Weight();
		final DynamicColor colorFill = DynamicColor.createColor(this.paint.fill, mtx);
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
			listSegmentStroke.createSegmentListStroke(listPoints, this.paint.strokeWidth, this.paint.lineCap,
					this.paint.lineJoin, this.paint.miterLimit);
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
	public void drawShapePoints(
			final List<List<Vector2f>> out,
			final int recurtionMax,
			final float threshold,
			final Matrix2x3f basicTrans,
			final int level) {
		LOGGER.trace("{}DRAW Shape esvg::Polyline", spacingDist(level));
		final PathModel listElement = createPath();
		final Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);
		PointList listPoints;
		listPoints = listElement.generateListPoints(level, recurtionMax, threshold);
		listPoints.applyMatrix(mtx);
		for (final List<Point> it : listPoints.data) {
			final List<Vector2f> listPoint = new ArrayList<>();
			for (final Point itDot : it) {
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

		final String sss1 = element.getAttribute("points", "");
		if (sss1.length() == 0) {
			LOGGER.error("polyline: missing points attribute");
			return false;
		}
		sizeMax.value = Vector2f.ZERO;
		LOGGER.trace("Parse polyline : '{}'", sss1);
		final String[] elems = sss1.split(" ");
		for (final String elem : elems) {
			final Vector2f pos = Vector2f.valueOf(elem);
			this.listPoint.add(pos);
			sizeMax.value = Vector2f.max(sizeMax.value, pos);
		}
		return true;
	}
}

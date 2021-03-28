/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Line.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>

esvg::Line::Line(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	this.startPos.setValue(0,0);
	this.stopPos.setValue(0,0);
}

esvg::Line::~Line() {
	
}

boolean esvg::Line::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	// line must have a minimum size...
	this.paint.strokeWidth = 1;
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	etk::String content = _element.attributes["x1"];
	if (content.size() != 0) {
		this.startPos.setX(parseLength(content));
	}
	content = _element.attributes["y1"];
	if (content.size() != 0) {
		this.startPos.setY(parseLength(content));
	}
	content = _element.attributes["x2"];
	if (content.size() != 0) {
		this.stopPos.setX(parseLength(content));
	}
	content = _element.attributes["y2"];
	if (content.size() != 0) {
		this.stopPos.setY(parseLength(content));
	}
	_sizeMax.setValue(etk::max(this.startPos.x(), this.stopPos.x()),
	                  etk::max(this.startPos.y(), this.stopPos.y()));
	return true;
}

void esvg::Line::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Line " << this.startPos << " to " << this.stopPos);
}

esvg::render::Path esvg::Line::createPath() {
	esvg::render::Path out;
	out.clear();
	out.moveTo(false, this.startPos);
	out.lineTo(false, this.stopPos);
	out.stop();
	return out;
}

void esvg::Line::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::Line");
	
	esvg::render::Path listElement = createPath();
	
	mat2x3 mtx = this.transformMatrix;
	mtx *= _basicTrans;
	
	esvg::render::PointList listPoints;
	listPoints = listElement.generateListPoints(_level,
	                                            _myRenderer.getInterpolationRecurtionMax(),
	                                            _myRenderer.getInterpolationThreshold());
	//listPoints.applyMatrix(mtx);
	esvg::render::SegmentList listSegmentFill;
	esvg::render::SegmentList listSegmentStroke;
	esvg::render::Weight tmpFill;
	esvg::render::Weight tmpStroke;
	ememory::SharedPtr<esvg::render::DynamicColor> colorFill = esvg::render::createColor(this.paint.fill, mtx);
	ememory::SharedPtr<esvg::render::DynamicColor> colorStroke;
	if (this.paint.strokeWidth > 0.0f) {
		colorStroke = esvg::render::createColor(this.paint.stroke, mtx);
	}
	// Check if we need to display background
	// No background ...
	// check if we need to display stroke:
	if (colorStroke != null) {
		listSegmentStroke.createSegmentListStroke(listPoints,
		                                          this.paint.strokeWidth,
		                                          this.paint.lineCap,
		                                          this.paint.lineJoin,
		                                          this.paint.miterLimit);
		colorStroke->setViewPort(listSegmentStroke.getViewPort());
		listSegmentStroke.applyMatrix(mtx);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpStroke.generate(_myRenderer.getSize(),
		                   _myRenderer.getNumberSubScanLine(),
		                   listSegmentStroke);
	}
	// add on images:
	_myRenderer.print(tmpFill,
	                  colorFill,
	                  tmpStroke,
	                  colorStroke,
	                  this.paint.opacity);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
		_myRenderer.addDebugSegment(listElement.this.debugInformation);
	#endif
}


void esvg::Line::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                 int _recurtionMax,
                                 float _threshold,
                                 mat2x3& _basicTrans,
                                 int _level) {
	Log.verbose(spacingDist(_level) << "DRAW Shape esvg::Line");
	esvg::render::Path listElement = createPath();
	mat2x3 mtx = this.transformMatrix;
	mtx *= _basicTrans;
	esvg::render::PointList listPoints;
	listPoints = listElement.generateListPoints(_level, _recurtionMax, _threshold);
	listPoints.applyMatrix(mtx);
	for (auto &it : listPoints.this.data) {
		List<Vector2f> listPoint;
		for (auto &itDot : it) {
			listPoint.pushBack(itDot.this.pos);
		}
		_out.pushBack(listPoint);
	}
}


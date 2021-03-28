/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Rectangle.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>

esvg::Rectangle::Rectangle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	this.position.setValue(0,0);
	this.size.setValue(0,0);
	this.roundedCorner.setValue(0,0);
}

esvg::Rectangle::~Rectangle() {
	
}

boolean esvg::Rectangle::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	this.position.setValue(0.0f, 0.0f);
	this.size.setValue(0.0f, 0.0f);
	this.roundedCorner.setValue(0.0f, 0.0f);
	
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	parsePosition(_element, this.position, this.size);
	
	etk::String content = _element.attributes["rx"];
	if (content.size()!=0) {
		this.roundedCorner.setX(parseLength(content));
	}
	content = _element.attributes["ry"];
	if (content.size()!=0) {
		this.roundedCorner.setY(parseLength(content));
	}
	_sizeMax.setValue(this.position.x() + this.size.x() + this.paint.strokeWidth,
	                  this.position.y() + this.size.y() + this.paint.strokeWidth);
	return true;
}

void esvg::Rectangle::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Rectangle : pos=" << this.position << " size=" << this.size << " corner=" << this.roundedCorner);
}

esvg::render::Path esvg::Rectangle::createPath() {
	esvg::render::Path out;
	out.clear();
	if (    this.roundedCorner.x() == 0.0f
	     || this.roundedCorner.y() == 0.0f) {
		out.moveTo(false, this.position);
		out.lineToH(true, this.size.x());
		out.lineToV(true, this.size.y());
		out.lineToH(true, -this.size.x());
	} else {
		// Rounded rectangle
		out.moveTo(false, this.position + Vector2f(this.roundedCorner.x(), 0.0f));
		out.lineToH(true, this.size.x()-this.roundedCorner.x()*2.0f);
		out.curveTo(true, Vector2f(this.roundedCorner.x()*esvg::kappa90, 0.0f),
		                  Vector2f(this.roundedCorner.x(),               this.roundedCorner.y() * (1.0f - esvg::kappa90)),
		                  Vector2f(this.roundedCorner.x(),               this.roundedCorner.y()) );
		out.lineToV(true, this.size.y()-this.roundedCorner.y()*2.0f);
		out.curveTo(true, Vector2f(0.0f,                                         this.roundedCorner.y() * esvg::kappa90),
		                  Vector2f(-this.roundedCorner.x()* (1.0f - esvg::kappa90), this.roundedCorner.y()),
		                  Vector2f(-this.roundedCorner.x(),                         this.roundedCorner.y()) );
		out.lineToH(true, -(this.size.x()-this.roundedCorner.x()*2.0f));
		out.curveTo(true, Vector2f(-this.roundedCorner.x()*esvg::kappa90, 0.0f),
		                  Vector2f(-this.roundedCorner.x(),               -this.roundedCorner.y() * (1.0f - esvg::kappa90)),
		                  Vector2f(-this.roundedCorner.x(),               -this.roundedCorner.y()) );
		out.lineToV(true, -(this.size.y()-this.roundedCorner.y()*2.0f));
		out.curveTo(true, Vector2f(0.0f,                                        -this.roundedCorner.y() * esvg::kappa90),
		                  Vector2f(this.roundedCorner.x()* (1.0f - esvg::kappa90), -this.roundedCorner.y()),
		                  Vector2f(this.roundedCorner.x(),                         -this.roundedCorner.y()) );
	}
	out.close();
	return out;
}

void esvg::Rectangle::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::Rectangle: fill=" << this.paint.fill.first << "/" << this.paint.fill.second
	                                 << " stroke=" << this.paint.stroke.first << "/" << this.paint.stroke.second);
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
	if (colorFill != null) {
		listSegmentFill.createSegmentList(listPoints);
		colorFill->setViewPort(listSegmentFill.getViewPort());
		listSegmentFill.applyMatrix(mtx);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpFill.generate(_myRenderer.getSize(),
		                 _myRenderer.getNumberSubScanLine(),
		                 listSegmentFill);
	}
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
	#endif
}


void esvg::Rectangle::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                      int _recurtionMax,
                                      float _threshold,
                                      mat2x3& _basicTrans,
                                      int _level) {
	Log.verbose(spacingDist(_level) << "DRAW Shape esvg::Rectangle");
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

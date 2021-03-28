/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Circle.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>

esvg::Circle::Circle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Circle::~Circle() {
	
}

boolean esvg::Circle::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	this.radius = 0.0;
	this.position.setValue(0,0);
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	etk::String content = _element.attributes["cx"];
	if (content.size()!=0) {
		this.position.setX(parseLength(content));
	}
	content = _element.attributes["cy"];
	if (content.size()!=0) {
		this.position.setY(parseLength(content));
	}
	content = _element.attributes["r"];
	if (content.size()!=0) {
		this.radius = parseLength(content);
	} else {
		Log.error("(l "<<_element.getPos()<<") Circle \"r\" is not present");
		return false;
	}
	if (0 > this.radius) {
		this.radius = 0;
		Log.error("(l "<<_element.getPos()<<") Circle \"r\" is negative");
		return false;
	}
	_sizeMax.setValue(this.position.x() + this.radius, this.position.y() + this.radius);
	return true;
}

void esvg::Circle::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Circle " << this.position << " radius=" << this.radius);
}

esvg::render::Path esvg::Circle::createPath() {
	esvg::render::Path out;
	
	out.clear();
	out.moveTo(false, this.position + Vector2f(this.radius, 0.0f));
	out.curveTo(false,
	            this.position + Vector2f(this.radius,                this.radius*esvg::kappa90),
	            this.position + Vector2f(this.radius*esvg::kappa90,  this.radius),
	            this.position + Vector2f(0.0f,                    this.radius));
	out.curveTo(false,
	            this.position + Vector2f(-this.radius*esvg::kappa90, this.radius),
	            this.position + Vector2f(-this.radius,               this.radius*esvg::kappa90),
	            this.position + Vector2f(-this.radius,               0.0f));
	out.curveTo(false,
	            this.position + Vector2f(-this.radius,               -this.radius*esvg::kappa90),
	            this.position + Vector2f(-this.radius*esvg::kappa90, -this.radius),
	            this.position + Vector2f(0.0f,                    -this.radius));
	out.curveTo(false,
	            this.position + Vector2f(this.radius*esvg::kappa90,  -this.radius),
	            this.position + Vector2f(this.radius,                -this.radius*esvg::kappa90),
	            this.position + Vector2f(this.radius,                0.0f));
	out.close();
	return out;
}

void esvg::Circle::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::Circle");
	if (this.radius <= 0.0f) {
		Log.verbose(spacingDist(_level+1) << "Too small radius" << this.radius);
		return;
	}
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

void esvg::Circle::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                   int _recurtionMax,
                                   float _threshold,
                                   mat2x3& _basicTrans,
                                   int _level) {
	Log.verbose(spacingDist(_level) << "DRAW Shape esvg::Circle");
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


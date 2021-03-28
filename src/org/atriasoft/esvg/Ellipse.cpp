/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Ellipse.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>

esvg::Ellipse::Ellipse(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Ellipse::~Ellipse() {
	
}

boolean esvg::Ellipse::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	this.c.setValue(0,0);
	this.r.setValue(0,0);
	
	etk::String content = _element.attributes["cx"];
	if (content.size()!=0) {
		this.c.setX(parseLength(content));
	}
	content = _element.attributes["cy"];
	if (content.size()!=0) {
		this.c.setY(parseLength(content));
	}
	content = _element.attributes["rx"];
	if (content.size()!=0) {
		this.r.setX(parseLength(content));
	} else {
		Log.error("(l "<<_element.getPos()<<") Ellipse \"rx\" is not present");
		return false;
	}
	content = _element.attributes["ry"];
	if (content.size()!=0) {
		this.r.setY(parseLength(content));
	} else {
		Log.error("(l "<<_element.getPos()<<") Ellipse \"ry\" is not present");
		return false;
	}
	_sizeMax.setValue(this.c.x() + this.r.x(), this.c.y() + this.r.y());
	
	return true;
}

void esvg::Ellipse::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Ellipse c=" << this.c << " r=" << this.r);
}


esvg::render::Path esvg::Ellipse::createPath() {
	esvg::render::Path out;
	out.clear();
	out.moveTo(false, this.c + Vector2f(this.r.x(), 0.0f));
	out.curveTo(false,
	            this.c + Vector2f(this.r.x(),                this.r.y()*esvg::kappa90),
	            this.c + Vector2f(this.r.x()*esvg::kappa90,  this.r.y()),
	            this.c + Vector2f(0.0f,                   this.r.y()));
	out.curveTo(false,
	            this.c + Vector2f(-this.r.x()*esvg::kappa90, this.r.y()),
	            this.c + Vector2f(-this.r.x(),               this.r.y()*esvg::kappa90),
	            this.c + Vector2f(-this.r.x(),               0.0f));
	out.curveTo(false,
	            this.c + Vector2f(-this.r.x(),               -this.r.y()*esvg::kappa90),
	            this.c + Vector2f(-this.r.x()*esvg::kappa90, -this.r.y()),
	            this.c + Vector2f(0.0f,                   -this.r.y()));
	out.curveTo(false,
	            this.c + Vector2f(this.r.x()*esvg::kappa90,  -this.r.y()),
	            this.c + Vector2f(this.r.x(),                -this.r.y()*esvg::kappa90),
	            this.c + Vector2f(this.r.x(),                0.0f));
	out.close();
	return out;
}

void esvg::Ellipse::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::Ellipse");
	if (    this.r.x()<=0.0f
	     || this.r.y()<=0.0f) {
		Log.verbose(spacingDist(_level+1) << "Too small radius" << this.r);
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


void esvg::Ellipse::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                    int _recurtionMax,
                                    float _threshold,
                                    mat2x3& _basicTrans,
                                    int _level) {
	Log.verbose(spacingDist(_level) << "DRAW Shape esvg::Ellipse");
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


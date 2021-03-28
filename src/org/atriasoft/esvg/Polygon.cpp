/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Polygon.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>

esvg::Polygon::Polygon(PaintState parentPaintState) : esvg::Base(parentPaintState) {
	
}

esvg::Polygon::~Polygon() {
	
}

boolean esvg::Polygon::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	Log.verbose("parsed P1.   trans: " << this.transformMatrix);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	Log.verbose("parsed P2.   trans: " << this.transformMatrix);
	
	const etk::String sss1 = _element.attributes["points"];
	if (sss1.size() == 0) {
		Log.error("(l "/*<<_element->Pos()*/<<") polygon: missing points attribute");
		return false;
	}
	const char * sss = sss1.c_str();
	_sizeMax.setValue(0,0);
	Log.verbose("Parse polygon : \"" << sss << "\"");
	while ('\0' != sss[0]) {
		Vector2f pos(0,0);
		int n;
		if (sscanf(sss, "%f,%f%n", &pos.this.floats[0], &pos.this.floats[1], &n) == 2) {
			this.listPoint.pushBack(pos);
			sss += n;
			_sizeMax.setValue(etk::max(_sizeMax.x(), pos.x()),
			                  etk::max(_sizeMax.y(), pos.y()));
			if(sss[0] == ' ' || sss[0] == ',') {
				sss++;
			}
		} else {
			break;
		}
	}
	return true;
}

void esvg::Polygon::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Polygon nbPoint=" << this.listPoint.size());
}

esvg::render::Path esvg::Polygon::createPath() {
	esvg::render::Path out;
	out.moveTo(false, this.listPoint[0]);
	for(size_t iii=1; iii< this.listPoint.size(); iii++) {
		out.lineTo(false, this.listPoint[iii]);
	}
	out.close();
	return out;
}

void esvg::Polygon::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::Polygon");
	
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


void esvg::Polygon::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                    int _recurtionMax,
                                    float _threshold,
                                    mat2x3& _basicTrans,
                                    int _level) {
	Log.verbose(spacingDist(_level) << "DRAW Shape esvg::Polygon");
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


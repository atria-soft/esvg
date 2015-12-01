/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Polygon.h>
#include <esvg/render/Path.h>
#include <esvg/render/Weight.h>

#undef __class__
#define __class__	"Polygon"

esvg::Polygon::Polygon(PaintState parentPaintState) : esvg::Base(parentPaintState) {
	
}

esvg::Polygon::~Polygon() {
	
}

bool esvg::Polygon::parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element == nullptr) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	SVG_VERBOSE("parsed P1.   trans: " << m_transformMatrix);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	SVG_VERBOSE("parsed P2.   trans: " << m_transformMatrix);
	
	const std::string sss1 = _element->getAttribute("points");
	if (sss1.size() == 0) {
		SVG_ERROR("(l "/*<<_element->Pos()*/<<") polygon: missing points attribute");
		return false;
	}
	const char * sss = sss1.c_str();
	_sizeMax.setValue(0,0);
	SVG_VERBOSE("Parse polygon : \"" << sss << "\"");
	while ('\0' != sss[0]) {
		vec2 pos(0,0);
		int32_t n;
		if (sscanf(sss, "%f,%f%n", &pos.m_floats[0], &pos.m_floats[1], &n) == 2) {
			m_listPoint.push_back(pos);
			sss += n;
			_sizeMax.setValue(std::max(_sizeMax.x(), pos.x()),
			                  std::max(_sizeMax.y(), pos.y()));
			if(sss[0] == ' ' || sss[0] == ',') {
				sss++;
			}
		} else {
			break;
		}
	}
	return true;
}

void esvg::Polygon::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Polygon nbPoint=" << m_listPoint.size());
}

void esvg::Polygon::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Polygon");
	
	esvg::render::Path listElement;
	listElement.moveTo(false, m_listPoint[0]);
	for( int32_t iii=1; iii< m_listPoint.size(); iii++) {
		listElement.lineTo(false, m_listPoint[iii]);
	}
	listElement.close();
	
	mat2 mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	esvg::render::PointList listPoints;
	listPoints = listElement.generateListPoints(_level,
	                                            _myRenderer.getInterpolationRecurtionMax(),
	                                            _myRenderer.getInterpolationThreshold());
	esvg::render::SegmentList listSegmentFill;
	esvg::render::SegmentList listSegmentStroke;
	esvg::render::Weight tmpFill;
	esvg::render::Weight tmpStroke;
	// Check if we need to display background
	if (m_paint.fill.a() != 0x00) {
		listSegmentFill.createSegmentList(listPoints);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpFill.generate(_myRenderer.getSize(),
		                 _myRenderer.getNumberSubScanLine(),
		                 listSegmentFill);
	}
	// check if we need to display stroke:
	if (    m_paint.strokeWidth > 0
	     && m_paint.stroke.a() != 0x00) {
		listSegmentStroke.createSegmentListStroke(listPoints,
		                                          m_paint.strokeWidth,
		                                          m_paint.lineCap,
		                                          m_paint.lineJoin,
		                                          m_paint.miterLimit);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpStroke.generate(_myRenderer.getSize(),
		                   _myRenderer.getNumberSubScanLine(),
		                   listSegmentStroke);
	}
	// add on images:
	_myRenderer.print(tmpFill,
	                  m_paint.fill,
	                  tmpStroke,
	                  m_paint.stroke,
	                  m_paint.opacity);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
	#endif
}


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Rectangle.h>
#include <esvg/render/Path.h>
#include <esvg/render/Weight.h>

#undef __class__
#define __class__	"Rectangle"


esvg::Rectangle::Rectangle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	m_position.setValue(0,0);
	m_size.setValue(0,0);
	m_roundedCorner.setValue(0,0);
}

esvg::Rectangle::~Rectangle() {
	
}

bool esvg::Rectangle::parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element == nullptr) {
		return false;
	}
	m_position.setValue(0.0f, 0.0f);
	m_size.setValue(0.0f, 0.0f);
	m_roundedCorner.setValue(0.0f, 0.0f);
	
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	parsePosition(_element, m_position, m_size);
	
	std::string content = _element->getAttribute("rx");
	if (content.size()!=0) {
		m_roundedCorner.setX(parseLength(content));
	}
	content = _element->getAttribute("ry");
	if (content.size()!=0) {
		m_roundedCorner.setY(parseLength(content));
	}
	_sizeMax.setValue(m_position.x() + m_size.x() + m_paint.strokeWidth,
	                  m_position.y() + m_size.y() + m_paint.strokeWidth);
	return true;
}

void esvg::Rectangle::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Rectangle : pos=" << m_position << " size=" << m_size << " corner=" << m_roundedCorner);
}

void esvg::Rectangle::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Rectangle : fill=" << m_paint.fill << " stroke=" << m_paint.stroke);
	// TODO : rounded corner ...
	esvg::render::Path listElement;
	listElement.clear();
	listElement.moveTo(false, m_position);
	listElement.lineToH(true, m_size.x());
	listElement.lineToV(true, m_size.y());
	listElement.lineToH(true, -m_size.x());
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
		listSegmentStroke.createSegmentListStroke(listPoints);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpStroke.generate(_myRenderer.getSize(),
		                   _myRenderer.getNumberSubScanLine(),
		                   listSegmentStroke);
	}
	// add on images:
	_myRenderer.print(tmpFill,
	                  m_paint.fill,
	                  tmpStroke,
	                  m_paint.stroke);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
	#endif
}


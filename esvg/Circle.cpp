/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Circle.h>
#include <esvg/render/Path.h>
#include <esvg/render/Weight.h>

#undef __class__
#define __class__	"Circle"

esvg::Circle::Circle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Circle::~Circle() {
	
}

bool esvg::Circle::parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	m_radius = 0.0;
	m_position.setValue(0,0);
	if (_element == nullptr) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string content = _element->getAttribute("cx");
	if (content.size()!=0) {
		m_position.setX(parseLength(content));
	}
	content = _element->getAttribute("cy");
	if (content.size()!=0) {
		m_position.setY(parseLength(content));
	}
	content = _element->getAttribute("r");
	if (content.size()!=0) {
		m_radius = parseLength(content);
	} else {
		SVG_ERROR("(l "<<_element->getPos()<<") Circle \"r\" is not present");
		return false;
	}
	if (0 > m_radius) {
		m_radius = 0;
		SVG_ERROR("(l "<<_element->getPos()<<") Circle \"r\" is negative");
		return false;
	}
	_sizeMax.setValue(m_position.x() + m_radius, m_position.y() + m_radius);
	return true;
}

void esvg::Circle::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Circle " << m_position << " radius=" << m_radius);
}


void esvg::Circle::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Circle");
	if (m_radius <= 0.0f) {
		SVG_VERBOSE(spacingDist(_level+1) << "Too small radius" << m_radius);
		return;
	}
	esvg::render::Path listElement;
	listElement.clear();
	listElement.moveTo(false, m_position + vec2(m_radius, 0.0f));
	listElement.curveTo(false,
	                    m_position + vec2(m_radius,                m_radius*esvg::kappa90),
	                    m_position + vec2(m_radius*esvg::kappa90,  m_radius),
	                    m_position + vec2(0.0f,                    m_radius));
	listElement.curveTo(false,
	                    m_position + vec2(-m_radius*esvg::kappa90, m_radius),
	                    m_position + vec2(-m_radius,               m_radius*esvg::kappa90),
	                    m_position + vec2(-m_radius,               0.0f));
	listElement.curveTo(false,
	                    m_position + vec2(-m_radius,               -m_radius*esvg::kappa90),
	                    m_position + vec2(-m_radius*esvg::kappa90, -m_radius),
	                    m_position + vec2(0.0f,                    -m_radius));
	listElement.curveTo(false,
	                    m_position + vec2(m_radius*esvg::kappa90,  -m_radius),
	                    m_position + vec2(m_radius,                -m_radius*esvg::kappa90),
	                    m_position + vec2(m_radius,                0.0f));
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
	                  m_paint.stroke,
	                  m_paint.opacity);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
	#endif
}


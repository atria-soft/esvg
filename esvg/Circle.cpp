/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Circle.h>
#include <esvg/render/Path.h>
#include <esvg/render/Weight.h>

esvg::Circle::Circle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Circle::~Circle() {
	
}

bool esvg::Circle::parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) {
	m_radius = 0.0;
	m_position.setValue(0,0);
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string content = _element.attributes["cx"];
	if (content.size()!=0) {
		m_position.setX(parseLength(content));
	}
	content = _element.attributes["cy"];
	if (content.size()!=0) {
		m_position.setY(parseLength(content));
	}
	content = _element.attributes["r"];
	if (content.size()!=0) {
		m_radius = parseLength(content);
	} else {
		ESVG_ERROR("(l "<<_element.getPos()<<") Circle \"r\" is not present");
		return false;
	}
	if (0 > m_radius) {
		m_radius = 0;
		ESVG_ERROR("(l "<<_element.getPos()<<") Circle \"r\" is negative");
		return false;
	}
	_sizeMax.setValue(m_position.x() + m_radius, m_position.y() + m_radius);
	return true;
}

void esvg::Circle::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Circle " << m_position << " radius=" << m_radius);
}

esvg::render::Path esvg::Circle::createPath() {
	esvg::render::Path out;
	
	out.clear();
	out.moveTo(false, m_position + vec2(m_radius, 0.0f));
	out.curveTo(false,
	            m_position + vec2(m_radius,                m_radius*esvg::kappa90),
	            m_position + vec2(m_radius*esvg::kappa90,  m_radius),
	            m_position + vec2(0.0f,                    m_radius));
	out.curveTo(false,
	            m_position + vec2(-m_radius*esvg::kappa90, m_radius),
	            m_position + vec2(-m_radius,               m_radius*esvg::kappa90),
	            m_position + vec2(-m_radius,               0.0f));
	out.curveTo(false,
	            m_position + vec2(-m_radius,               -m_radius*esvg::kappa90),
	            m_position + vec2(-m_radius*esvg::kappa90, -m_radius),
	            m_position + vec2(0.0f,                    -m_radius));
	out.curveTo(false,
	            m_position + vec2(m_radius*esvg::kappa90,  -m_radius),
	            m_position + vec2(m_radius,                -m_radius*esvg::kappa90),
	            m_position + vec2(m_radius,                0.0f));
	out.close();
	return out;
}

void esvg::Circle::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Circle");
	if (m_radius <= 0.0f) {
		ESVG_VERBOSE(spacingDist(_level+1) << "Too small radius" << m_radius);
		return;
	}
	esvg::render::Path listElement = createPath();
	
	mat2 mtx = m_transformMatrix;
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
	ememory::SharedPtr<esvg::render::DynamicColor> colorFill = esvg::render::createColor(m_paint.fill, mtx);
	ememory::SharedPtr<esvg::render::DynamicColor> colorStroke;
	if (m_paint.strokeWidth > 0.0f) {
		colorStroke = esvg::render::createColor(m_paint.stroke, mtx);
	}
	// Check if we need to display background
	if (colorFill != nullptr) {
		listSegmentFill.createSegmentList(listPoints);
		colorFill->setViewPort(listSegmentFill.getViewPort());
		listSegmentFill.applyMatrix(mtx);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpFill.generate(_myRenderer.getSize(),
		                 _myRenderer.getNumberSubScanLine(),
		                 listSegmentFill);
	}
	// check if we need to display stroke:
	if (colorStroke != nullptr) {
		listSegmentStroke.createSegmentListStroke(listPoints,
		                                          m_paint.strokeWidth,
		                                          m_paint.lineCap,
		                                          m_paint.lineJoin,
		                                          m_paint.miterLimit);
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
	                  m_paint.opacity);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
	#endif
}

void esvg::Circle::drawShapePoints(std::vector<std::vector<vec2>>& _out,
                                   int32_t _recurtionMax,
                                   float _threshold,
                                   mat2& _basicTrans,
                                   int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW Shape esvg::Circle");
	esvg::render::Path listElement = createPath();
	mat2 mtx = m_transformMatrix;
	mtx *= _basicTrans;
	esvg::render::PointList listPoints;
	listPoints = listElement.generateListPoints(_level, _recurtionMax, _threshold);
	listPoints.applyMatrix(mtx);
	for (auto &it : listPoints.m_data) {
		std::vector<vec2> listPoint;
		for (auto &itDot : it) {
			listPoint.push_back(itDot.m_pos);
		}
		_out.push_back(listPoint);
	}
}


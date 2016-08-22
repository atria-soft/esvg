/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Rectangle.h>
#include <esvg/render/Path.h>
#include <esvg/render/Weight.h>

esvg::Rectangle::Rectangle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	m_position.setValue(0,0);
	m_size.setValue(0,0);
	m_roundedCorner.setValue(0,0);
}

esvg::Rectangle::~Rectangle() {
	
}

bool esvg::Rectangle::parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element.exist() == false) {
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
	
	std::string content = _element.attributes["rx"];
	if (content.size()!=0) {
		m_roundedCorner.setX(parseLength(content));
	}
	content = _element.attributes["ry"];
	if (content.size()!=0) {
		m_roundedCorner.setY(parseLength(content));
	}
	_sizeMax.setValue(m_position.x() + m_size.x() + m_paint.strokeWidth,
	                  m_position.y() + m_size.y() + m_paint.strokeWidth);
	return true;
}

void esvg::Rectangle::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Rectangle : pos=" << m_position << " size=" << m_size << " corner=" << m_roundedCorner);
}

esvg::render::Path esvg::Rectangle::createPath() {
	esvg::render::Path out;
	out.clear();
	if (    m_roundedCorner.x() == 0.0f
	     || m_roundedCorner.y() == 0.0f) {
		out.moveTo(false, m_position);
		out.lineToH(true, m_size.x());
		out.lineToV(true, m_size.y());
		out.lineToH(true, -m_size.x());
	} else {
		// Rounded rectangle
		out.moveTo(false, m_position + vec2(m_roundedCorner.x(), 0.0f));
		out.lineToH(true, m_size.x()-m_roundedCorner.x()*2.0f);
		out.curveTo(true, vec2(m_roundedCorner.x()*esvg::kappa90, 0.0f),
		                  vec2(m_roundedCorner.x(),               m_roundedCorner.y() * (1.0f - esvg::kappa90)),
		                  vec2(m_roundedCorner.x(),               m_roundedCorner.y()) );
		out.lineToV(true, m_size.y()-m_roundedCorner.y()*2.0f);
		out.curveTo(true, vec2(0.0f,                                         m_roundedCorner.y() * esvg::kappa90),
		                  vec2(-m_roundedCorner.x()* (1.0f - esvg::kappa90), m_roundedCorner.y()),
		                  vec2(-m_roundedCorner.x(),                         m_roundedCorner.y()) );
		out.lineToH(true, -(m_size.x()-m_roundedCorner.x()*2.0f));
		out.curveTo(true, vec2(-m_roundedCorner.x()*esvg::kappa90, 0.0f),
		                  vec2(-m_roundedCorner.x(),               -m_roundedCorner.y() * (1.0f - esvg::kappa90)),
		                  vec2(-m_roundedCorner.x(),               -m_roundedCorner.y()) );
		out.lineToV(true, -(m_size.y()-m_roundedCorner.y()*2.0f));
		out.curveTo(true, vec2(0.0f,                                        -m_roundedCorner.y() * esvg::kappa90),
		                  vec2(m_roundedCorner.x()* (1.0f - esvg::kappa90), -m_roundedCorner.y()),
		                  vec2(m_roundedCorner.x(),                         -m_roundedCorner.y()) );
	}
	out.close();
	return out;
}

void esvg::Rectangle::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Rectangle: fill=" << m_paint.fill.first << "/" << m_paint.fill.second
	                                 << " stroke=" << m_paint.stroke.first << "/" << m_paint.stroke.second);
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


void esvg::Rectangle::drawShapePoints(std::vector<std::vector<vec2>>& _out,
                                      int32_t _recurtionMax,
                                      float _threshold,
                                      mat2& _basicTrans,
                                      int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW Shape esvg::Rectangle");
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

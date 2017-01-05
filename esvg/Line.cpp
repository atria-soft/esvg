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
	m_startPos.setValue(0,0);
	m_stopPos.setValue(0,0);
}

esvg::Line::~Line() {
	
}

bool esvg::Line::parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) {
	// line must have a minimum size...
	m_paint.strokeWidth = 1;
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string content = _element.attributes["x1"];
	if (content.size() != 0) {
		m_startPos.setX(parseLength(content));
	}
	content = _element.attributes["y1"];
	if (content.size() != 0) {
		m_startPos.setY(parseLength(content));
	}
	content = _element.attributes["x2"];
	if (content.size() != 0) {
		m_stopPos.setX(parseLength(content));
	}
	content = _element.attributes["y2"];
	if (content.size() != 0) {
		m_stopPos.setY(parseLength(content));
	}
	_sizeMax.setValue(std::max(m_startPos.x(), m_stopPos.x()),
	                  std::max(m_startPos.y(), m_stopPos.y()));
	return true;
}

void esvg::Line::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Line " << m_startPos << " to " << m_stopPos);
}

esvg::render::Path esvg::Line::createPath() {
	esvg::render::Path out;
	out.clear();
	out.moveTo(false, m_startPos);
	out.lineTo(false, m_stopPos);
	out.stop();
	return out;
}

void esvg::Line::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Line");
	
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
	// No background ...
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
		_myRenderer.addDebugSegment(listElement.m_debugInformation);
	#endif
}


void esvg::Line::drawShapePoints(std::vector<std::vector<vec2>>& _out,
                                 int32_t _recurtionMax,
                                 float _threshold,
                                 mat2& _basicTrans,
                                 int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW Shape esvg::Line");
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


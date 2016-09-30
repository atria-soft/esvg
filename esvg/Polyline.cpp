/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Polyline.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>

esvg::Polyline::Polyline(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Polyline::~Polyline() {
	
}

bool esvg::Polyline::parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) {
	// line must have a minimum size...
	m_paint.strokeWidth = 1;
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string sss1 = _element.attributes["points"];
	if (sss1.size() == 0) {
		ESVG_ERROR("(l "<<_element.getPos()<<") polyline: missing points attribute");
		return false;
	}
	_sizeMax.setValue(0,0);
	ESVG_VERBOSE("Parse polyline : \"" << sss1 << "\"");
	const char* sss = sss1.c_str();
	while ('\0' != sss[0]) {
		vec2 pos;
		int32_t n;
		if (sscanf(sss, "%f,%f %n", &pos.m_floats[0], &pos.m_floats[1], &n) == 2) {
			m_listPoint.push_back(pos);
			_sizeMax.setValue(std::max(_sizeMax.x(), pos.x()),
			                  std::max(_sizeMax.y(), pos.y()));
			sss += n;
		} else {
			break;
		}
	}
	return true;
}

void esvg::Polyline::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Polyline nbPoint=" << m_listPoint.size());
}


esvg::render::Path esvg::Polyline::createPath() {
	esvg::render::Path out;
	out.clear();
	out.moveTo(false, m_listPoint[0]);
	for( int32_t iii=1; iii< m_listPoint.size(); iii++) {
		out.lineTo(false, m_listPoint[iii]);
	}
	out.stop();
	return out;
}

void esvg::Polyline::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Polyline");
	
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


void esvg::Polyline::drawShapePoints(std::vector<std::vector<vec2>>& _out,
                                     int32_t _recurtionMax,
                                     float _threshold,
                                     mat2& _basicTrans,
                                     int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW Shape esvg::Polyline");
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

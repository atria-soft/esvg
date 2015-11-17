/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Line.h>

#undef __class__
#define __class__	"Line"

esvg::Line::Line(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	m_startPos.setValue(0,0);
	m_stopPos.setValue(0,0);
}

esvg::Line::~Line() {
	
}

bool esvg::Line::parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	// line must have a minimum size...
	m_paint.strokeWidth = 1;
	if (_element == nullptr) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string content = _element->getAttribute("x1");
	if (content.size()!=0) {
		m_startPos.setX(parseLength(content));
	}
	content = _element->getAttribute("y1");
	if (content.size()!=0) {
		m_startPos.setY(parseLength(content));
	}
	content = _element->getAttribute("x2");
	if (content.size()!=0) {
		m_stopPos.setX(parseLength(content));
	}
	content = _element->getAttribute("y2");
	if (content.size()!=0) {
		m_stopPos.setY(parseLength(content));
	}
	_sizeMax.setValue(std::max(m_startPos.x(), m_stopPos.x()),
	                  std::max(m_startPos.y(), m_stopPos.y()));
	return true;
}

void esvg::Line::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Line " << m_startPos << " to " << m_stopPos);
}

void esvg::Line::aggDraw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Line");
	# if 0
	esvg::RenderPath path;
	path.start_new_path();
	path.move_to(m_startPos.x(), m_startPos.y());
	path.line_to(m_stopPos.x(), m_stopPos.y());
	/*
	// configure the end of the line : 
	switch (m_paint.lineCap) {
		case esvg::LINECAP_SQUARE:
			path.line_cap(agg::square_cap);
			break;
		case esvg::LINECAP_ROUND:
			path.line_cap(agg::round_cap);
			break;
		default: // esvg::LINECAP_BUTT
			path.line_cap(agg::butt_cap);
			break;
	}
	switch (m_paint.lineJoin) {
		case esvg::LINEJOIN_BEVEL:
			path.line_join(agg::bevel_join);
			break;
		case esvg::LINEJOIN_ROUND:
			path.line_join(agg::round_join);
			break;
		default: // esvg::LINEJOIN_MITER
			path.line_join(agg::miter_join);
			break;
	}
	*/
	mat2 mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	if (m_paint.strokeWidth > 0) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// drawing as an outline
		agg::conv_stroke<esvg::RenderPath> myPolygonStroke(path);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<esvg::RenderPath>, mat2> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
	#endif
}



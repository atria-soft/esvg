/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Polygon.h>

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
	
	#if 0
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	
	esvg::RenderPath path;
	path.start_new_path();
	
	path.move_to(m_listPoint[0].x(), m_listPoint[0].y());
	for( int32_t iii=1; iii< m_listPoint.size(); iii++) {
		path.line_to(m_listPoint[iii].x(), m_listPoint[iii].y());
	}
	path.close_polygon();
	/*
	// configure the end of the line:
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
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<esvg::RenderPath, mat2> trans(path, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
	
	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
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


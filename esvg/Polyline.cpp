/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Polyline.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_path_storage.h>

esvg::Polyline::Polyline(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Polyline::~Polyline(void) {
	
}

bool esvg::Polyline::parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	// line must have a minimum size...
	m_paint.strokeWidth = 1;
	if (NULL == _element) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string sss1 = _element->getAttribute("points");
	if (sss1.size() == 0) {
		SVG_ERROR("(l "<<_element->getPos()<<") polyline: missing points attribute");
		return false;
	}
	_sizeMax.setValue(0,0);
	SVG_VERBOSE("Parse polyline : \"" << sss1 << "\"");
	const char* sss = sss1.c_str();
	while ('\0' != sss[0]) {
		etk::Vector2D<float> pos;
		int32_t n;
		if (sscanf(sss, "%f,%f %n", &pos.m_floats[0], &pos.m_floats[1], &n) == 2) {
			m_listPoint.push_back(pos);
			_sizeMax.setValue(etk_max(_sizeMax.x(), pos.x()),
			                  etk_max(_sizeMax.y(), pos.y()));
			sss += n;
		} else {
			break;
		}
	}
	return true;
}

void esvg::Polyline::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Polyline nbPoint=" << m_listPoint.size());
}


void esvg::Polyline::aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans) {
	agg::path_storage path;
	path.start_new_path();
	path.move_to(m_listPoint[0].x(), m_listPoint[0].y());
	for( int32_t iii=1; iii< m_listPoint.size(); iii++) {
		path.line_to(m_listPoint[iii].x(), m_listPoint[iii].y());
	}
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
	
	agg::trans_affine mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	if (m_paint.strokeWidth > 0) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// drawing as an outline
		agg::conv_stroke<agg::path_storage> myPolygonStroke(path);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::path_storage>, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
}



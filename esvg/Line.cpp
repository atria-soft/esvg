/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/Debug.h>
#include <esvg/Line.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_path_storage.h>

esvg::Line::Line(PaintState parentPaintState) : esvg::Base(parentPaintState)
{
	m_startPos.setValue(0,0);
	m_stopPos.setValue(0,0);
}

esvg::Line::~Line(void)
{
	
}

bool esvg::Line::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	// line must have a minimum size...
	m_paint.strokeWidth = 1;
	if (NULL==_element) {
		return false;
	}
	ParseTransform(_element);
	ParsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	etk::UString content = _element->GetAttribute("x1");
	if (content.Size()!=0) {
		m_startPos.setX(ParseLength(content));
	}
	content = _element->GetAttribute("y1");
	if (content.Size()!=0) {
		m_startPos.setY(ParseLength(content));
	}
	content = _element->GetAttribute("x2");
	if (content.Size()!=0) {
		m_stopPos.setX(ParseLength(content));
	}
	content = _element->GetAttribute("y2");
	if (content.Size()!=0) {
		m_stopPos.setY(ParseLength(content));
	}
	_sizeMax.setValue(etk_max(m_startPos.x(), m_stopPos.x()),
	                  etk_max(m_startPos.y(), m_stopPos.y()));
	return true;
}

void esvg::Line::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Line " << m_startPos << " to " << m_stopPos);
}


void esvg::Line::AggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	agg::path_storage path;
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
	agg::trans_affine mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	if (m_paint.strokeWidth > 0) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::path_storage> myPolygonStroke(path);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::path_storage>, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
}



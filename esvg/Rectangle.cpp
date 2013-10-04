/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/Debug.h>
#include <esvg/Rectangle.h>
#include <agg/agg_rounded_rect.h>
#include <agg/agg_conv_stroke.h>

#undef __class__
#define __class__	"Rectangle"


esvg::Rectangle::Rectangle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	m_position.setValue(0,0);
	m_size.setValue(0,0);
	m_roundedCorner.setValue(0,0);
}

esvg::Rectangle::~Rectangle(void) {
	
}

bool esvg::Rectangle::parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	if (NULL == _element) {
		return false;
	}
	m_position.setValue(0,0);
	m_size.setValue(0,0);
	m_roundedCorner.setValue(0,0);
	
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	parsePosition(_element, m_position, m_size);
	
	etk::UString content = _element->getAttribute("rx");
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

void esvg::Rectangle::aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans) {
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	// Creating a rounded rectangle
	agg::rounded_rect rect_r(m_position.x(), m_position.y(), m_position.x()+m_size.x(), m_position.y()+m_size.y(), m_roundedCorner.x());
	rect_r.radius(m_roundedCorner.x(), m_roundedCorner.y());
	rect_r.normalize_radius();
	
	agg::trans_affine  mtx = m_transformMatrix;
	// herited modifications ...
	mtx *= _basicTrans;
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::rounded_rect, agg::trans_affine> trans(rect_r, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}

	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// drawing as an outline
		agg::conv_stroke<agg::rounded_rect> rect_p(rect_r);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		rect_p.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::rounded_rect>, agg::trans_affine> transStroke(rect_p, mtx);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}

}


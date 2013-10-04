/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/Debug.h>
#include <esvg/Circle.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_ellipse.h>

#undef __class__
#define __class__	"Circle"

esvg::Circle::Circle(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Circle::~Circle(void) {
	
}

bool esvg::Circle::parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	m_radius = 0.0;
	m_position.setValue(0,0);
	if (NULL == _element) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	etk::UString content = _element->getAttribute("cx");
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

void esvg::Circle::display(int32_t _spacing)
{
	SVG_DEBUG(spacingDist(_spacing) << "Circle " << m_position << " radius=" << m_radius);
}


void esvg::Circle::aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	// Creating an ellipse
	agg::ellipse myCircle(m_position.x(), m_position.y(), m_radius, m_radius, 0);
	
	// Calculate transformation matrix ...
	agg::trans_affine  mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	// set the filling mode : 
	_myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::ellipse, agg::trans_affine> trans(myCircle, mtx);
		_myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
	
	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// drawing as an outline
		agg::conv_stroke<agg::ellipse> myCircleStroke(myCircle);
		myCircleStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::ellipse>, agg::trans_affine> transStroke(myCircleStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}

}


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Circle.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_ellipse.h>


svg::Circle::Circle(PaintState _parentPaintState) : svg::Base(_parentPaintState)
{
	
}

svg::Circle::~Circle(void)
{
	
}

bool svg::Circle::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	m_radius = 0.0;
	m_position.setValue(0,0);
	if (NULL==_element) {
		return false;
	}
	ParseTransform(_element);
	ParsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	etk::UString content = _element->GetAttribute("cx");
	if (content.Size()!=0) {
		m_position.setX(ParseLength(content));
	}
	content = _element->GetAttribute("cy");
	if (content.Size()!=0) {
		m_position.setY(ParseLength(content));
	}
	content = _element->GetAttribute("r");
	if (content.Size()!=0) {
		m_radius = ParseLength(content);
	} else {
		SVG_ERROR("(l "<<_element->Pos()<<") Circle \"r\" is not present");
		return false;
	}

	if (0 > m_radius) {
		m_radius = 0;
		SVG_ERROR("(l "<<_element->Pos()<<") Circle \"r\" is negative");
		return false;
	}
	_sizeMax.setValue(m_position.x() + m_radius, m_position.y() + m_radius);
	return true;
}

void svg::Circle::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Circle " << m_position << " radius=" << m_radius);
}


void svg::Circle::AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
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
		// Drawing as an outline
		agg::conv_stroke<agg::ellipse> myCircleStroke(myCircle);
		myCircleStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::ellipse>, agg::trans_affine> transStroke(myCircleStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}

}


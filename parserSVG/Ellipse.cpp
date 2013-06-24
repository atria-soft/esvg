/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Ellipse.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_ellipse.h>

svg::Ellipse::Ellipse(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	
}

svg::Ellipse::~Ellipse(void)
{
	
}

bool svg::Ellipse::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	if (NULL==_element) {
		return false;
	}
	ParseTransform(_element);
	ParsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	m_c.setValue(0,0);
	m_r.setValue(0,0);
	
	etk::UString content = _element->GetAttribute("cx");
	if (content.Size()!=0) {
		m_c.setX(ParseLength(content));
	}
	content = _element->GetAttribute("cy");
	if (content.Size()!=0) {
		m_c.setY(ParseLength(content));
	}
	content = _element->GetAttribute("rx");
	if (content.Size()!=0) {
		m_r.setX(ParseLength(content));
	} else {
		SVG_ERROR("(l "<<_element->Pos()<<") Ellipse \"rx\" is not present");
		return false;
	}
	content = _element->GetAttribute("ry");
	if (content.Size()!=0) {
		m_r.setY(ParseLength(content));
	} else {
		SVG_ERROR("(l "<<_element->Pos()<<") Ellipse \"ry\" is not present");
		return false;
	}
	_sizeMax.setValue(m_c.x() + m_r.x(), m_c.y() + m_r.y());
	
	return true;
}

void svg::Ellipse::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Ellipse c=" << m_c << " r=" << m_r);
}


void svg::Ellipse::AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	// Creating an ellipse
	agg::ellipse myEllipse(m_c.x(), m_c.y(), m_r.x(), m_r.y(), 0);
	
	// Calculate transformation matrix ...
	agg::trans_affine  mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	// set the filling mode : 
	_myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::ellipse, agg::trans_affine> trans(myEllipse, mtx);
		_myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}

	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::ellipse> myEllipseStroke(myEllipse);
		myEllipseStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::ellipse>, agg::trans_affine> transStroke(myEllipseStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}

}



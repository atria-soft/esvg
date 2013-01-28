/**
 *******************************************************************************
 * @file parserSVG/Rectangle.cpp
 * @brief basic rectangle parsing (Sources)
 * @author Edouard DUPIN
 * @date 20/03/2012
 * @par Project
 * parserSVG
 *
 * @par Copyright
 * Copyright 2011 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Rectangle.h>
#include <agg/agg_rounded_rect.h>
#include <agg/agg_conv_stroke.h>

svg::Rectangle::Rectangle(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	m_position.setValue(0,0);
	m_size.setValue(0,0);
	m_roundedCorner.setValue(0,0);
}

svg::Rectangle::~Rectangle(void)
{
	
}

bool svg::Rectangle::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax)
{
	m_position.setValue(0,0);
	m_size.setValue(0,0);
	m_roundedCorner.setValue(0,0);
	
	ParseTransform(node);
	ParsePaintAttr(node);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= parentTrans;
	
	ParsePosition(node, m_position, m_size);
	
	const char * content = node->ToElement()->Attribute("rx");
	if (NULL != content) {
		m_roundedCorner.setX(ParseLength(content));
	}
	content = node->ToElement()->Attribute("ry");
	if (NULL != content) {
		m_roundedCorner.setY(ParseLength(content));
	}
	sizeMax.setValue(m_position.x() + m_size.x() + m_paint.strokeWidth,
	                 m_position.y() + m_size.y() + m_paint.strokeWidth);
	return true;
}

void svg::Rectangle::Display(int32_t spacing)
{
	SVG_DEBUG(SpacingDist(spacing) << "Rectangle : pos=" << m_position << " size=" << m_size << " corner=" << m_roundedCorner);
}

void svg::Rectangle::AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans)
{
	myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	// Creating a rounded rectangle
	agg::rounded_rect rect_r(m_position.x(), m_position.y(), m_position.x()+m_size.x(), m_position.y()+m_size.y(), m_roundedCorner.x());
	rect_r.radius(m_roundedCorner.x(), m_roundedCorner.y());
	rect_r.normalize_radius();
	
	agg::trans_affine  mtx = m_transformMatrix;
	// herited modifications ...
	mtx *= basicTrans;
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::rounded_rect, agg::trans_affine> trans(rect_r, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}

	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::rounded_rect> rect_p(rect_r);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		rect_p.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::rounded_rect>, agg::trans_affine> transStroke(rect_p, mtx);
		myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}

}


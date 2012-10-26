/**
 *******************************************************************************
 * @file parserSVG/Circle.cpp
 * @brief basic circle parsing (Sources)
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
#include <parserSVG/Circle.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_ellipse.h>


svg::Circle::Circle(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	
}

svg::Circle::~Circle(void)
{
	
}

bool svg::Circle::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax)
{
	m_radius = 0.0;
	m_position.x = 0.0;
	m_position.y = 0.0;
	ParseTransform(node);
	ParsePaintAttr(node);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= parentTrans;
	
	const char * content = node->ToElement()->Attribute("cx");
	if (NULL != content) {
		m_position.x = ParseLength(content);
	}
	content = node->ToElement()->Attribute("cy");
	if (NULL != content) {
		m_position.y = ParseLength(content);
	}
	content = node->ToElement()->Attribute("r");
	if (NULL != content) {
		m_radius = ParseLength(content);
	} else {
		SVG_ERROR("(l "<<node->Row()<<") Circle \"r\" is not present");
		return false;
	}

	if (0 > m_radius) {
		m_radius = 0;
		SVG_ERROR("(l "<<node->Row()<<") Circle \"r\" is negative");
		return false;
	}
	sizeMax.x = m_position.x + m_radius;
	sizeMax.y = m_position.y + m_radius;
	return true;
}

void svg::Circle::Display(int32_t spacing)
{
	SVG_DEBUG(SpacingDist(spacing) << "Circle " << m_position << " radius=" << m_radius);
}


void svg::Circle::AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans)
{
	myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	// Creating an ellipse
	agg::ellipse myCircle(m_position.x, m_position.y, m_radius, m_radius, 0);
	
	// Calculate transformation matrix ...
	agg::trans_affine  mtx = m_transformMatrix;
	mtx *= basicTrans;
	
	// set the filling mode : 
	myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::ellipse, agg::trans_affine> trans(myCircle, mtx);
		myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}

	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::ellipse> myCircleStroke(myCircle);
		myCircleStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::ellipse>, agg::trans_affine> transStroke(myCircleStroke, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}

}


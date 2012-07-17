/**
 *******************************************************************************
 * @file parserSVG/Ellipse.cpp
 * @brief basic ellipse parsing (Sources)
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
#include <parserSVG/Ellipse.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_ellipse.h>

svg::Ellipse::Ellipse(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	
}

svg::Ellipse::~Ellipse(void)
{
	
}

bool svg::Ellipse::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax)
{
	ParseTransform(node);
	ParsePaintAttr(node);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= parentTrans;
	
	m_c.x = 0.0;
	m_c.y = 0.0;
	m_r.x = 0.0;
	m_r.y = 0.0;
	
	const char * content = node->ToElement()->Attribute("cx");
	if (NULL != content) {
		m_c.x = ParseLength(content);
	}
	content = node->ToElement()->Attribute("cy");
	if (NULL != content) {
		m_c.y = ParseLength(content);
	}
	content = node->ToElement()->Attribute("rx");
	if (NULL != content) {
		m_r.x = ParseLength(content);
	} else {
		SVG_ERROR("(l "<<node->Row()<<") Ellipse \"rx\" is not present");
		return false;
	}
	content = node->ToElement()->Attribute("ry");
	if (NULL != content) {
		m_r.y = ParseLength(content);
	} else {
		SVG_ERROR("(l "<<node->Row()<<") Ellipse \"ry\" is not present");
		return false;
	}
	sizeMax.x = m_c.x + m_r.x;
	sizeMax.y = m_c.y + m_r.y;
	
	return true;
}

void svg::Ellipse::Display(int32_t spacing)
{
	SVG_DEBUG(SpacingDist(spacing) << "Ellipse c=" << m_c << " r=" << m_r);
}


void svg::Ellipse::AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans)
{
	myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.red, m_paint.fill.green, m_paint.fill.blue, m_paint.fill.alpha));
	// Creating an ellipse
	agg::ellipse myEllipse(m_c.x, m_c.y, m_r.x, m_r.y, 0);
	
	// Calculate transformation matrix ...
	agg::trans_affine  mtx = m_transformMatrix;
	mtx *= basicTrans;
	
	// set the filling mode : 
	myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
	
	if (m_paint.fill.alpha != 0x00) {
		agg::conv_transform<agg::ellipse, agg::trans_affine> trans(myEllipse, mtx);
		myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}

	if (m_paint.strokeWidth > 0 && m_paint.stroke.alpha!=0x00 ) {
		myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.red, m_paint.stroke.green, m_paint.stroke.blue, m_paint.stroke.alpha));
		// Drawing as an outline
		agg::conv_stroke<agg::ellipse> myEllipseStroke(myEllipse);
		myEllipseStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::ellipse>, agg::trans_affine> transStroke(myEllipseStroke, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}

}



/**
 *******************************************************************************
 * @file parserSVG/Polygon.cpp
 * @brief basic poligon parsing (Sources)
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
#include <parserSVG/Polygon.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_path_storage.h>

svg::Polygon::Polygon(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	
}

svg::Polygon::~Polygon(void)
{
	
}

bool svg::Polygon::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax)
{
	ParseTransform(node);
	ParsePaintAttr(node);
	
	SVG_VERBOSE("parsed P1.   trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= parentTrans;
	
	SVG_VERBOSE("parsed P2.   trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	
	const char *sss = node->ToElement()->Attribute("points");
	if (NULL == sss) {
		SVG_ERROR("(l "<<node->Row()<<") polygon: missing points attribute");
		return false;
	}
	sizeMax.x = 0;
	sizeMax.y = 0;
	SVG_VERBOSE("Parse polygon : \"" << sss << "\"");
	while ('\0' != sss[0]) {
		etk::Vector2D<float> pos;
		int32_t n;
		if (sscanf(sss, "%f,%f%n", &pos.x, &pos.y, &n) == 2) {
			m_listPoint.PushBack(pos);
			sss += n;
			sizeMax.x = etk_max(sizeMax.x, pos.x);
			sizeMax.y = etk_max(sizeMax.y, pos.y);
			if(sss[0] == ' ' || sss[0] == ',') {
				sss++;
			}
		} else {
			break;
		}
	}
	return true;
}

void svg::Polygon::Display(int32_t spacing)
{
	SVG_DEBUG(SpacingDist(spacing) << "Polygon nbPoint=" << m_listPoint.Size());
}

void svg::Polygon::AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans)
{
	myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	
	agg::path_storage path;
	path.start_new_path();
	
	path.move_to(m_listPoint[0].x, m_listPoint[0].y);
	for( int32_t iii=1; iii< m_listPoint.Size(); iii++) {
		path.line_to(m_listPoint[iii].x, m_listPoint[iii].y);
	}
	path.close_polygon();
	/*
	// configure the end of the line : 
	switch (m_paint.lineCap) {
		case svg::LINECAP_SQUARE:
			path.line_cap(agg::square_cap);
			break;
		case svg::LINECAP_ROUND:
			path.line_cap(agg::round_cap);
			break;
		default: // svg::LINECAP_BUTT
			path.line_cap(agg::butt_cap);
			break;
	}
	switch (m_paint.lineJoin) {
		case svg::LINEJOIN_BEVEL:
			path.line_join(agg::bevel_join);
			break;
		case svg::LINEJOIN_ROUND:
			path.line_join(agg::round_join);
			break;
		default: // svg::LINEJOIN_MITER
			path.line_join(agg::miter_join);
			break;
	}
	*/
	
	agg::trans_affine mtx = m_transformMatrix;
	mtx *= basicTrans;
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::path_storage, agg::trans_affine> trans(path, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}
	
	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::path_storage> myPolygonStroke(path);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::path_storage>, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}
}


/**
 *******************************************************************************
 * @file parserSVG/Path.cpp
 * @brief basic path parsing (Sources)
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
#include <parserSVG/Path.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_conv_dash.h>
#include <agg/agg_conv_curve.h>
#include <agg/agg_conv_contour.h>
#include <agg/agg_conv_smooth_poly1.h>

svg::Path::Path(PaintState parentPaintState) : svg::Base(parentPaintState)
{
	
}

svg::Path::~Path(void)
{
	
}


// return the next char position ... (after 'X' or NULL)
const char * extractCmd(const char * input, char& cmd, etk::Vector<float>& outputList)
{
	if (*input == '\0') {
		return NULL;
	}
	outputList.Clear();
	cmd = '\0';
	const char * outputPointer = NULL;
	if (!( (input[0] <= 'Z' && input[0] >= 'A') || (input[0] <= 'z' && input[0] >= 'a') ) ) {
		SVG_ERROR("Error in the SVG Path : \"" << input << "\"");
		return NULL;
	}
	cmd = input[0];
	SVG_VERBOSE("Find command : " << cmd);
	if (input[1] == '\0') {
		return &input[1];
	}
	int32_t iii=1;
	// extract every float separated by a ' ' or a ','
	float element;
	char spacer[10];
	int32_t nbElementRead;
	while(    sscanf(&input[iii], "%1[, ]%f%n", spacer, &element, &nbElementRead) == 2
	       || sscanf(&input[iii], "%f%n", &element, &nbElementRead) == 1) {
		SVG_VERBOSE("Find element : " << element);
		outputList.PushBack(element);
		iii += nbElementRead;
	}
	outputPointer = &input[iii];
	while(*outputPointer!= '\0' && *outputPointer == ' ') {
		outputPointer++;
	}
	//outputPointer++;
	return outputPointer;
}

bool svg::Path::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax)
{
	ParseTransform(node);
	ParsePaintAttr(node);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= parentTrans;
	
	
	const char *elementXML = node->ToElement()->Attribute("d");
	if (NULL == elementXML) {
		SVG_ERROR("(l "<<node->Row()<<") path: missing 'p' attribute");
		return false;
	}
	SVG_VERBOSE("Parse Path : \"" << elementXML << "\"");
	
	char command;
	etk::Vector<float> listDot;
	
	for( const char *sss=extractCmd(elementXML, command, listDot);
	     NULL != sss;
	     sss=extractCmd(sss, command, listDot) ) {
		pathBasic_ts pathElement;
		memset(&pathElement, 0, 1*sizeof(pathBasic_ts));
		switch(command) {
			case 'M': // Move To (absolute)
			case 'L': // Line To (absolute)
			case 'V': // Vertical Line To (absolute)
			case 'H': // Horizantal Line To (absolute)
			case 'Q': // Quadratic Bezier curve (absolute)
			case 'T': // smooth quadratic Bezier curve to (absolute)
			case 'C': // curve to (absolute)
			case 'S': // smooth curve to (absolute)
			case 'A': // elliptical Arc (absolute)
			case 'Z': // closepath (absolute)
				pathElement.relative = false;
				break;
			default : // else (relative)
				pathElement.relative = true;
				break;
		}
		switch(command) {
			case 'M': // Move To (absolute)
			case 'm': // Move To (relative)
				// 2 Elements ...
				if(listDot.Size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_MOVETO;
				if (listDot.Size() >= 2) {
					pathElement.element[0] = listDot[0];
					pathElement.element[1] = listDot[1];
					m_listElement.PushBack(pathElement);
				}
				pathElement.cmd = svg::PATH_ENUM_LINETO;
				for(int32_t iii=2; iii<listDot.Size(); iii+=2) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'L': // Line To (absolute)
			case 'l': // Line To (relative)
				// 2 Elements ...
				if(listDot.Size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_LINETO;
				for(int32_t iii=0; iii<listDot.Size(); iii+=2) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'V': // Vertical Line To (absolute)
			case 'v': // Vertical Line To (relative)
				// 1 Element ...
				if(listDot.Size() == 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_LINETO_V;
				for(int32_t iii=0; iii<listDot.Size(); iii+=1) {
					pathElement.element[0] = listDot[iii];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'H': // Horizantal Line To (absolute)
			case 'h': // Horizantal Line To (relative)
				// 1 Element ...
				if(listDot.Size() == 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_LINETO_H;
				for(int32_t iii=0; iii<listDot.Size(); iii+=1) {
					pathElement.element[0] = listDot[iii];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'Q': // Quadratic Bezier curve (absolute)
			case 'q': // Quadratic Bezier curve (relative)
				// 4 Elements ...
				if(listDot.Size()%4 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_BEZIER_CURVETO;
				for(int32_t iii=0; iii<listDot.Size(); iii+=4) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					pathElement.element[2] = listDot[iii+2];
					pathElement.element[3] = listDot[iii+3];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'T': // smooth quadratic Bezier curve to (absolute)
			case 't': // smooth quadratic Bezier curve to (relative)
				// 2 Elements ...
				if(listDot.Size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_BEZIER_SMOTH_CURVETO;
				for(int32_t iii=0; iii<listDot.Size(); iii+=2) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'C': // curve to (absolute)
			case 'c': // curve to (relative)
				// 6 Elements ...
				if(listDot.Size()%6 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_CURVETO;
				for(int32_t iii=0; iii<listDot.Size(); iii+=6) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					pathElement.element[2] = listDot[iii+2];
					pathElement.element[3] = listDot[iii+3];
					pathElement.element[4] = listDot[iii+4];
					pathElement.element[5] = listDot[iii+5];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'S': // smooth curve to (absolute)
			case 's': // smooth curve to (relative)
				// 4 Elements ...
				if(listDot.Size()%4 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_SMOTH_CURVETO;
				for(int32_t iii=0; iii<listDot.Size(); iii+=4) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					pathElement.element[2] = listDot[iii+2];
					pathElement.element[3] = listDot[iii+3];
					m_listElement.PushBack(pathElement);
				}
				break;
				
			case 'A': // elliptical Arc (absolute)
			case 'a': // elliptical Arc (relative)
				// 7 Elements ...
				if(listDot.Size()%7 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_ELLIPTIC;
				for(int32_t iii=0; iii<listDot.Size(); iii+=7) {
					pathElement.element[0] = listDot[iii];
					pathElement.element[1] = listDot[iii+1];
					pathElement.element[2] = listDot[iii+2];
					pathElement.element[3] = listDot[iii+3];
					pathElement.element[4] = listDot[iii+4];
					pathElement.element[5] = listDot[iii+5];
					pathElement.element[6] = listDot[iii+6];
					m_listElement.PushBack(pathElement);
				}
				break;
			case 'Z': // closepath (absolute)
			case 'z': // closepath (relative)
				// 0 Element ...
				if(listDot.Size() != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.Size() );
					break;
				}
				pathElement.cmd = svg::PATH_ENUM_STOP;
				m_listElement.PushBack(pathElement);
				break;
			default:
				SVG_ERROR ("Unknow error : \"" << command << "\"");
		}
	}
	
	return true;
}

void svg::Path::Display(int32_t spacing)
{
	SVG_DEBUG(SpacingDist(spacing) << "Path");
	for(int32_t iii=0; iii<m_listElement.Size(); iii++) {
		switch (m_listElement[iii].cmd) {
			case PATH_ENUM_STOP:
				SVG_DEBUG(SpacingDist(spacing+4) << "STOP");
				break;
			case PATH_ENUM_MOVETO:
				SVG_DEBUG(SpacingDist(spacing+4) << "MOVETO (" << m_listElement[iii].element[0] << "," << m_listElement[iii].element[1] << ")" );
				break;
			case PATH_ENUM_LINETO:
				SVG_DEBUG(SpacingDist(spacing+4) << "LINETO (" << m_listElement[iii].element[0] << "," << m_listElement[iii].element[1] << ")" );
				break;
			case PATH_ENUM_LINETO_H:
				SVG_DEBUG(SpacingDist(spacing+4) << "LINETO_H (" << m_listElement[iii].element[0] << ")" );
				break;
			case PATH_ENUM_LINETO_V:
				SVG_DEBUG(SpacingDist(spacing+4) << "LINETO_V (" << m_listElement[iii].element[0] << ")" );
				break;
			case PATH_ENUM_CURVETO:
				SVG_DEBUG(SpacingDist(spacing+4) << "CURVETO (" << m_listElement[iii].element[0] << 
				                                            "," << m_listElement[iii].element[1] << 
				                                            "," << m_listElement[iii].element[2] << 
				                                            "," << m_listElement[iii].element[3] << 
				                                            "," << m_listElement[iii].element[4] << 
				                                            "," << m_listElement[iii].element[5] << ")" );
				break;
			case PATH_ENUM_SMOTH_CURVETO:
				SVG_DEBUG(SpacingDist(spacing+4) << "SMOTH_CURVETO (" << m_listElement[iii].element[0] <<
				                                                  "," << m_listElement[iii].element[1] << 
				                                                  "," << m_listElement[iii].element[2] << 
				                                                  "," << m_listElement[iii].element[3] <<  ")" );
				break;
			case PATH_ENUM_BEZIER_CURVETO:
				SVG_DEBUG(SpacingDist(spacing+4) << "BEZIER_CURVETO (" << m_listElement[iii].element[0] << 
				                                                   "," << m_listElement[iii].element[1] << 
				                                                   "," << m_listElement[iii].element[2] << 
				                                                   "," << m_listElement[iii].element[3] << ")" );
				break;
			case PATH_ENUM_BEZIER_SMOTH_CURVETO:
				SVG_DEBUG(SpacingDist(spacing+4) << "BEZIER_SMOTH_CURVETO (" << m_listElement[iii].element[0] << "," << m_listElement[iii].element[1] << ")" );
				break;
			case PATH_ENUM_ELLIPTIC:
				SVG_DEBUG(SpacingDist(spacing+4) << "ELLIPTIC (TODO...)" );
				// show explanation at : http://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
				break;
			default:
				SVG_DEBUG(SpacingDist(spacing+4) << "????" );
				break;
		}
	}
}



void svg::Path::AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans)
{
	myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	
	agg::path_storage path;
	path.start_new_path();
	
	
	for(int32_t iii=0; iii<m_listElement.Size(); iii++) {
		switch (m_listElement[iii].cmd) {
			case PATH_ENUM_STOP:
				AbstractCloseSubpath(path);
				break;
			case PATH_ENUM_MOVETO:
				AbstractMoveTo(path, m_listElement[iii].relative,
				               m_listElement[iii].element[0],
				               m_listElement[iii].element[1] );
				break;
			case PATH_ENUM_LINETO:
				AbstractLineTo(path, m_listElement[iii].relative,
				               m_listElement[iii].element[0],
				               m_listElement[iii].element[1] );
				break;
			case PATH_ENUM_LINETO_H:
				AbstractHLineTo(path, m_listElement[iii].relative,
				                m_listElement[iii].element[0] );
				break;
			case PATH_ENUM_LINETO_V:
				AbstractVLineTo(path, m_listElement[iii].relative,
				                m_listElement[iii].element[0] );
				break;
			case PATH_ENUM_CURVETO:
				AbstractCurve4(path, m_listElement[iii].relative,
				               m_listElement[iii].element[0],
				               m_listElement[iii].element[1],
				               m_listElement[iii].element[2],
				               m_listElement[iii].element[3],
				               m_listElement[iii].element[4],
				               m_listElement[iii].element[5] );
				//SVG_INFO(" draw : PATH_ENUM_CURVETO");
				break;
			case PATH_ENUM_SMOTH_CURVETO:
				AbstractCurve4(path, m_listElement[iii].relative,
				               m_listElement[iii].element[0],
				               m_listElement[iii].element[1],
				               m_listElement[iii].element[2],
				               m_listElement[iii].element[3] );
				//SVG_INFO(" draw : PATH_ENUM_SMOTH_CURVETO");
				break;
			case PATH_ENUM_BEZIER_CURVETO:
				AbstractCurve3(path, m_listElement[iii].relative,
				               m_listElement[iii].element[0],
				               m_listElement[iii].element[1],
				               m_listElement[iii].element[2],
				               m_listElement[iii].element[3] );
				//SVG_INFO(" draw : PATH_ENUM_BEZIER_CURVETO");
				break;
			case PATH_ENUM_BEZIER_SMOTH_CURVETO:
				AbstractCurve3(path, m_listElement[iii].relative,
				               m_listElement[iii].element[0],
				               m_listElement[iii].element[1] );
				//SVG_INFO(" draw : PATH_ENUM_BEZIER_SMOTH_CURVETO");
				break;
			case PATH_ENUM_ELLIPTIC:
				SVG_TODO("Elliptic arc is not implemented NOW ...");
				break;
			default:
				SVG_ERROR("Unknow PATH commant (internal error)");
				break;
		}
	}
	
	agg::trans_affine mtx = m_transformMatrix;
	mtx *= basicTrans;
	
	agg::conv_curve<agg::path_storage> curve(path);
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::conv_curve<agg::path_storage>, agg::trans_affine> trans(curve, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}
	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::conv_curve<agg::path_storage> > myPolygonStroke(curve);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::conv_curve<agg::path_storage> >, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(myRenderer.m_rasterizer, myRenderer.m_scanLine, *myRenderer.m_renderArea);
	}
}


void svg::Path::AbstractMoveTo(agg::path_storage& path, bool rel, double x, double y)
{
	if(true == rel) {
		path.rel_to_abs(&x, &y);
	}
	path.move_to(x, y);
}

void svg::Path::AbstractLineTo(agg::path_storage& path, bool rel, double x, double y)
{
	if(true == rel) {
		path.rel_to_abs(&x, &y);
	}
	path.line_to(x, y);
}

void svg::Path::AbstractHLineTo(agg::path_storage& path, bool rel, double x)
{
	double x2 = 0.0;
	double y2 = 0.0;
	if(0!=path.total_vertices()) {
		path.vertex(path.total_vertices() - 1, &x2, &y2);
		if(true == rel) {
			x += x2;
		}
		path.line_to(x, y2);
	}
}

void svg::Path::AbstractVLineTo(agg::path_storage& path, bool rel, double y)
{
	double x2 = 0.0;
	double y2 = 0.0;
	if(path.total_vertices()) {
		path.vertex(path.total_vertices() - 1, &x2, &y2);
		if(true == rel) {
			y += y2;
		}
		path.line_to(x2, y);
	}
}

void svg::Path::AbstractCurve3(agg::path_storage& path, bool rel, double x1, double y1, double x,  double y)
{
	if(true == rel) {
		path.rel_to_abs(&x1, &y1);
		path.rel_to_abs(&x,  &y);
	}
	path.curve3(x1, y1, x, y);
}

void svg::Path::AbstractCurve3(agg::path_storage& path, bool rel, double x, double y)
{
	if(true == rel) {
		path.curve3_rel(x, y);
	} else {
		path.curve3(x, y);
	}
}

void svg::Path::AbstractCurve4(agg::path_storage& path, bool rel, double x1, double y1, double x2, double y2, double x, double y)
{
	if(true == rel) {
		path.rel_to_abs(&x1, &y1);
		path.rel_to_abs(&x2, &y2);
		path.rel_to_abs(&x,  &y);
	}
	path.curve4(x1, y1, x2, y2, x, y);
}

void svg::Path::AbstractCurve4(agg::path_storage& path, bool rel, double x2, double y2, double x,  double y)
{
	if(true == rel) {
		path.curve4_rel(x2, y2, x, y);
	} else {
		path.curve4(x2, y2, x, y);
	}
}

void svg::Path::AbstractCloseSubpath(agg::path_storage& path)
{
	path.end_poly(agg::path_flags_close);
}

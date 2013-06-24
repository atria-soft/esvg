/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Path.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_conv_dash.h>
#include <agg/agg_conv_curve.h>
#include <agg/agg_conv_contour.h>
#include <agg/agg_conv_smooth_poly1.h>

svg::Path::Path(PaintState _parentPaintState) : svg::Base(_parentPaintState)
{
	
}

svg::Path::~Path(void)
{
	
}


// return the next char position ... (after 'X' or NULL)
const char * extractCmd(const char* input, char& cmd, etk::Vector<float>& outputList)
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

bool svg::Path::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	if (NULL==_element) {
		return false;
	}
	ParseTransform(_element);
	ParsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	
	etk::UString elementXML1 = _element->GetAttribute("d");
	if (elementXML1.Size()==0) {
		SVG_ERROR("(l "<<_element->Pos()<<") path: missing 'p' attribute");
		return false;
	}
	SVG_VERBOSE("Parse Path : \"" << elementXML << "\"");
	
	char command;
	etk::Vector<float> listDot;
	
	etk::Char plop = elementXML1.c_str();
	const char* elementXML = plop;
	
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

void svg::Path::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Path");
	for(int32_t iii=0; iii<m_listElement.Size(); iii++) {
		switch (m_listElement[iii].cmd) {
			case PATH_ENUM_STOP:
				SVG_DEBUG(SpacingDist(_spacing+4) << "STOP");
				break;
			case PATH_ENUM_MOVETO:
				SVG_DEBUG(SpacingDist(_spacing+4) << "MOVETO (" << m_listElement[iii].element[0] << "," << m_listElement[iii].element[1] << ")" );
				break;
			case PATH_ENUM_LINETO:
				SVG_DEBUG(SpacingDist(_spacing+4) << "LINETO (" << m_listElement[iii].element[0] << "," << m_listElement[iii].element[1] << ")" );
				break;
			case PATH_ENUM_LINETO_H:
				SVG_DEBUG(SpacingDist(_spacing+4) << "LINETO_H (" << m_listElement[iii].element[0] << ")" );
				break;
			case PATH_ENUM_LINETO_V:
				SVG_DEBUG(SpacingDist(_spacing+4) << "LINETO_V (" << m_listElement[iii].element[0] << ")" );
				break;
			case PATH_ENUM_CURVETO:
				SVG_DEBUG(SpacingDist(_spacing+4) << "CURVETO (" << m_listElement[iii].element[0] << 
				                                             "," << m_listElement[iii].element[1] << 
				                                             "," << m_listElement[iii].element[2] << 
				                                             "," << m_listElement[iii].element[3] << 
				                                             "," << m_listElement[iii].element[4] << 
				                                             "," << m_listElement[iii].element[5] << ")" );
				break;
			case PATH_ENUM_SMOTH_CURVETO:
				SVG_DEBUG(SpacingDist(_spacing+4) << "SMOTH_CURVETO (" << m_listElement[iii].element[0] <<
				                                                   "," << m_listElement[iii].element[1] << 
				                                                   "," << m_listElement[iii].element[2] << 
				                                                   "," << m_listElement[iii].element[3] <<  ")" );
				break;
			case PATH_ENUM_BEZIER_CURVETO:
				SVG_DEBUG(SpacingDist(_spacing+4) << "BEZIER_CURVETO (" << m_listElement[iii].element[0] << 
				                                                    "," << m_listElement[iii].element[1] << 
				                                                    "," << m_listElement[iii].element[2] << 
				                                                    "," << m_listElement[iii].element[3] << ")" );
				break;
			case PATH_ENUM_BEZIER_SMOTH_CURVETO:
				SVG_DEBUG(SpacingDist(_spacing+4) << "BEZIER_SMOTH_CURVETO (" << m_listElement[iii].element[0] << "," << m_listElement[iii].element[1] << ")" );
				break;
			case PATH_ENUM_ELLIPTIC:
				SVG_DEBUG(SpacingDist(_spacing+4) << "ELLIPTIC (TODO...)" );
				// show explanation at : http://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
				break;
			default:
				SVG_DEBUG(SpacingDist(_spacing+4) << "????" );
				break;
		}
	}
}



void svg::Path::AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	
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
	mtx *= _basicTrans;
	
	agg::conv_curve<agg::path_storage> curve(path);
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::conv_curve<agg::path_storage>, agg::trans_affine> trans(curve, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::conv_curve<agg::path_storage> > myPolygonStroke(curve);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::conv_curve<agg::path_storage> >, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
}


void svg::Path::AbstractMoveTo(agg::path_storage& _path, bool _rel, double _x, double _y)
{
	if(true == _rel) {
		_path.rel_to_abs(&_x, &_y);
	}
	_path.move_to(_x, _y);
}

void svg::Path::AbstractLineTo(agg::path_storage& _path, bool _rel, double _x, double _y)
{
	if(true == _rel) {
		_path.rel_to_abs(&_x, &_y);
	}
	_path.line_to(_x, _y);
}

void svg::Path::AbstractHLineTo(agg::path_storage& _path, bool _rel, double _x)
{
	double x2 = 0.0;
	double y2 = 0.0;
	if(0!=_path.total_vertices()) {
		_path.vertex(_path.total_vertices() - 1, &x2, &y2);
		if(true == _rel) {
			_x += x2;
		}
		_path.line_to(_x, y2);
	}
}

void svg::Path::AbstractVLineTo(agg::path_storage& _path, bool _rel, double _y)
{
	double x2 = 0.0;
	double y2 = 0.0;
	if(_path.total_vertices()) {
		_path.vertex(_path.total_vertices() - 1, &x2, &y2);
		if(true == _rel) {
			_y += y2;
		}
		_path.line_to(x2, _y);
	}
}

void svg::Path::AbstractCurve3(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x, double _y)
{
	if(true == _rel) {
		_path.rel_to_abs(&_x1, &_y1);
		_path.rel_to_abs(&_x,  &_y);
	}
	_path.curve3(_x1, _y1, _x, _y);
}

void svg::Path::AbstractCurve3(agg::path_storage& _path, bool _rel, double _x, double _y)
{
	if(true == _rel) {
		_path.curve3_rel(_x, _y);
	} else {
		_path.curve3(_x, _y);
	}
}

void svg::Path::AbstractCurve4(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x2, double _y2, double _x, double _y)
{
	if(true == _rel) {
		_path.rel_to_abs(&_x1, &_y1);
		_path.rel_to_abs(&_x2, &_y2);
		_path.rel_to_abs(&_x,  &_y);
	}
	_path.curve4(_x1, _y1, _x2, _y2, _x, _y);
}

void svg::Path::AbstractCurve4(agg::path_storage& _path, bool _rel, double _x2, double _y2, double _x,  double _y)
{
	if(true == _rel) {
		_path.curve4_rel(_x2, _y2, _x, _y);
	} else {
		_path.curve4(_x2, _y2, _x, _y);
	}
}

void svg::Path::AbstractCloseSubpath(agg::path_storage& _path)
{
	_path.end_poly(agg::path_flags_close);
}

/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/Debug.h>
#include <esvg/Path.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_conv_dash.h>
#include <agg/agg_conv_curve.h>
#include <agg/agg_conv_contour.h>
#include <agg/agg_conv_smooth_poly1.h>

#undef __class__
#define __class__	"Path"

esvg::Path::Path(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Path::~Path(void) {
	
}


// return the next char position ... (after 'X' or NULL)
const char * extractCmd(const char* _input, char& _cmd, etk::Vector<float>& _outputList) {
	if (*_input == '\0') {
		return NULL;
	}
	_outputList.clear();
	_cmd = '\0';
	const char * outputPointer = NULL;
	if (!( (_input[0] <= 'Z' && _input[0] >= 'A') || (_input[0] <= 'z' && _input[0] >= 'a') ) ) {
		SVG_ERROR("Error in the SVG Path : \"" << _input << "\"");
		return NULL;
	}
	_cmd = _input[0];
	SVG_VERBOSE("Find command : " << _cmd);
	if (_input[1] == '\0') {
		return &_input[1];
	}
	int32_t iii=1;
	// extract every float separated by a ' ' or a ','
	float element;
	char spacer[10];
	int32_t nbElementRead;
	while(    sscanf(&_input[iii], "%1[, ]%f%n", spacer, &element, &nbElementRead) == 2
	       || sscanf(&_input[iii], "%f%n", &element, &nbElementRead) == 1) {
		SVG_VERBOSE("Find element : " << element);
		_outputList.pushBack(element);
		iii += nbElementRead;
	}
	outputPointer = &_input[iii];
	while(*outputPointer!= '\0' && *outputPointer == ' ') {
		outputPointer++;
	}
	//outputPointer++;
	return outputPointer;
}

bool esvg::Path::parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	if (NULL == _element) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	
	etk::UString elementXML1 = _element->getAttribute("d");
	if (elementXML1.size() == 0) {
		SVG_ERROR("(l "<<_element->getPos()<<") path: missing 'p' attribute");
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
		PathBasic pathElement;
		switch(command) {
			case 'M': // Move to (absolute)
			case 'L': // Line to (absolute)
			case 'V': // Vertical Line to (absolute)
			case 'H': // Horizantal Line to (absolute)
			case 'Q': // Quadratic Bezier curve (absolute)
			case 'T': // smooth quadratic Bezier curve to (absolute)
			case 'C': // curve to (absolute)
			case 'S': // smooth curve to (absolute)
			case 'A': // elliptical Arc (absolute)
			case 'Z': // closepath (absolute)
				pathElement.m_relative = false;
				break;
			default : // else (relative)
				pathElement.m_relative = true;
				break;
		}
		switch(command) {
			case 'M': // Move to (absolute)
			case 'm': // Move to (relative)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathMoveTo;
				if (listDot.size() >= 2) {
					pathElement.m_element[0] = listDot[0];
					pathElement.m_element[1] = listDot[1];
					m_listElement.pushBack(pathElement);
				}
				pathElement.m_cmd = esvg::pathLineTo;
				for(int32_t iii=2; iii<listDot.size(); iii+=2) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'L': // Line to (absolute)
			case 'l': // Line to (relative)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathLineTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=2) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'V': // Vertical Line to (absolute)
			case 'v': // Vertical Line to (relative)
				// 1 Element ...
				if(listDot.size() == 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathLineToV;
				for(int32_t iii=0; iii<listDot.size(); iii+=1) {
					pathElement.m_element[0] = listDot[iii];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'H': // Horizantal Line to (absolute)
			case 'h': // Horizantal Line to (relative)
				// 1 Element ...
				if(listDot.size() == 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathLineToH;
				for(int32_t iii=0; iii<listDot.size(); iii+=1) {
					pathElement.m_element[0] = listDot[iii];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'Q': // Quadratic Bezier curve (absolute)
			case 'q': // Quadratic Bezier curve (relative)
				// 4 Elements ...
				if(listDot.size()%4 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathBesizeCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'T': // smooth quadratic Bezier curve to (absolute)
			case 't': // smooth quadratic Bezier curve to (relative)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathBesizeSmothCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=2) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'C': // curve to (absolute)
			case 'c': // curve to (relative)
				// 6 Elements ...
				if(listDot.size()%6 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=6) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					pathElement.m_element[4] = listDot[iii+4];
					pathElement.m_element[5] = listDot[iii+5];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'S': // smooth curve to (absolute)
			case 's': // smooth curve to (relative)
				// 4 Elements ...
				if(listDot.size()%4 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathSmothCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					m_listElement.pushBack(pathElement);
				}
				break;
				
			case 'A': // elliptical Arc (absolute)
			case 'a': // elliptical Arc (relative)
				// 7 Elements ...
				if(listDot.size()%7 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathElliptic;
				for(int32_t iii=0; iii<listDot.size(); iii+=7) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					pathElement.m_element[4] = listDot[iii+4];
					pathElement.m_element[5] = listDot[iii+5];
					pathElement.m_element[6] = listDot[iii+6];
					m_listElement.pushBack(pathElement);
				}
				break;
			case 'Z': // closepath (absolute)
			case 'z': // closepath (relative)
				// 0 Element ...
				if(listDot.size() != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::pathStop;
				m_listElement.pushBack(pathElement);
				break;
			default:
				SVG_ERROR ("Unknow error : \"" << command << "\"");
		}
	}
	
	return true;
}

void esvg::Path::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Path");
	for(int32_t iii=0; iii<m_listElement.size(); iii++) {
		switch (m_listElement[iii].m_cmd) {
			case esvg::pathStop:
				SVG_DEBUG(spacingDist(_spacing+4) << "STOP");
				break;
			case esvg::pathMoveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "MOVETO (" << m_listElement[iii].m_element[0] << "," << m_listElement[iii].m_element[1] << ")" );
				break;
			case esvg::pathLineTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO (" << m_listElement[iii].m_element[0] << "," << m_listElement[iii].m_element[1] << ")" );
				break;
			case esvg::pathLineToH:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO_H (" << m_listElement[iii].m_element[0] << ")" );
				break;
			case esvg::pathLineToV:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO_V (" << m_listElement[iii].m_element[0] << ")" );
				break;
			case esvg::pathCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "CURVETO (" << m_listElement[iii].m_element[0] << 
				                                             "," << m_listElement[iii].m_element[1] << 
				                                             "," << m_listElement[iii].m_element[2] << 
				                                             "," << m_listElement[iii].m_element[3] << 
				                                             "," << m_listElement[iii].m_element[4] << 
				                                             "," << m_listElement[iii].m_element[5] << ")" );
				break;
			case esvg::pathSmothCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "SMOTH_CURVETO (" << m_listElement[iii].m_element[0] <<
				                                                   "," << m_listElement[iii].m_element[1] << 
				                                                   "," << m_listElement[iii].m_element[2] << 
				                                                   "," << m_listElement[iii].m_element[3] <<  ")" );
				break;
			case esvg::pathBesizeCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "BEZIER_CURVETO (" << m_listElement[iii].m_element[0] << 
				                                                    "," << m_listElement[iii].m_element[1] << 
				                                                    "," << m_listElement[iii].m_element[2] << 
				                                                    "," << m_listElement[iii].m_element[3] << ")" );
				break;
			case esvg::pathBesizeSmothCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "BEZIER_SMOTH_CURVETO (" << m_listElement[iii].m_element[0] << "," << m_listElement[iii].m_element[1] << ")" );
				break;
			case esvg::pathElliptic:
				SVG_DEBUG(spacingDist(_spacing+4) << "ELLIPTIC (TODO...)" );
				// show explanation at : http://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
				break;
			default:
				SVG_DEBUG(spacingDist(_spacing+4) << "????" );
				break;
		}
	}
}

void esvg::Path::aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans) {
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	
	agg::path_storage path;
	path.start_new_path();
	
	
	for(int32_t iii=0; iii<m_listElement.size(); iii++) {
		switch (m_listElement[iii].m_cmd) {
			case esvg::pathStop:
				abstractCloseSubpath(path);
				break;
			case esvg::pathMoveTo:
				abstractMoveTo(path, m_listElement[iii].m_relative,
				               m_listElement[iii].m_element[0],
				               m_listElement[iii].m_element[1] );
				break;
			case esvg::pathLineTo:
				abstractLineTo(path, m_listElement[iii].m_relative,
				               m_listElement[iii].m_element[0],
				               m_listElement[iii].m_element[1] );
				break;
			case esvg::pathLineToH:
				abstractHLineTo(path, m_listElement[iii].m_relative,
				                m_listElement[iii].m_element[0] );
				break;
			case esvg::pathLineToV:
				abstractVLineTo(path, m_listElement[iii].m_relative,
				                m_listElement[iii].m_element[0] );
				break;
			case esvg::pathCurveTo:
				abstractCurve4(path, m_listElement[iii].m_relative,
				               m_listElement[iii].m_element[0],
				               m_listElement[iii].m_element[1],
				               m_listElement[iii].m_element[2],
				               m_listElement[iii].m_element[3],
				               m_listElement[iii].m_element[4],
				               m_listElement[iii].m_element[5] );
				//SVG_INFO(" draw : esvg::pathCurveTo");
				break;
			case esvg::pathSmothCurveTo:
				abstractCurve4(path, m_listElement[iii].m_relative,
				               m_listElement[iii].m_element[0],
				               m_listElement[iii].m_element[1],
				               m_listElement[iii].m_element[2],
				               m_listElement[iii].m_element[3] );
				//SVG_INFO(" draw : esvg::pathSmothCurveTo");
				break;
			case esvg::pathBesizeCurveTo:
				abstractCurve3(path, m_listElement[iii].m_relative,
				               m_listElement[iii].m_element[0],
				               m_listElement[iii].m_element[1],
				               m_listElement[iii].m_element[2],
				               m_listElement[iii].m_element[3] );
				//SVG_INFO(" draw : esvg::pathBesizeCurveTo");
				break;
			case esvg::pathBesizeSmothCurveTo:
				abstractCurve3(path, m_listElement[iii].m_relative,
				               m_listElement[iii].m_element[0],
				               m_listElement[iii].m_element[1] );
				//SVG_INFO(" draw : esvg::pathBesizeSmothCurveTo");
				break;
			case esvg::pathElliptic:
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
		// drawing as an outline
		agg::conv_stroke<agg::conv_curve<agg::path_storage> > myPolygonStroke(curve);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::conv_curve<agg::path_storage> >, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
}


void esvg::Path::abstractMoveTo(agg::path_storage& _path, bool _rel, double _x, double _y) {
	if(true == _rel) {
		_path.rel_to_abs(&_x, &_y);
	}
	_path.move_to(_x, _y);
}

void esvg::Path::abstractLineTo(agg::path_storage& _path, bool _rel, double _x, double _y) {
	if(true == _rel) {
		_path.rel_to_abs(&_x, &_y);
	}
	_path.line_to(_x, _y);
}

void esvg::Path::abstractHLineTo(agg::path_storage& _path, bool _rel, double _x) {
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

void esvg::Path::abstractVLineTo(agg::path_storage& _path, bool _rel, double _y) {
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

void esvg::Path::abstractCurve3(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x, double _y) {
	if(true == _rel) {
		_path.rel_to_abs(&_x1, &_y1);
		_path.rel_to_abs(&_x,  &_y);
	}
	_path.curve3(_x1, _y1, _x, _y);
}

void esvg::Path::abstractCurve3(agg::path_storage& _path, bool _rel, double _x, double _y) {
	if(true == _rel) {
		_path.curve3_rel(_x, _y);
	} else {
		_path.curve3(_x, _y);
	}
}

void esvg::Path::abstractCurve4(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x2, double _y2, double _x, double _y) {
	if(true == _rel) {
		_path.rel_to_abs(&_x1, &_y1);
		_path.rel_to_abs(&_x2, &_y2);
		_path.rel_to_abs(&_x,  &_y);
	}
	_path.curve4(_x1, _y1, _x2, _y2, _x, _y);
}

void esvg::Path::abstractCurve4(agg::path_storage& _path, bool _rel, double _x2, double _y2, double _x,  double _y) {
	if(true == _rel) {
		_path.curve4_rel(_x2, _y2, _x, _y);
	} else {
		_path.curve4(_x2, _y2, _x, _y);
	}
}

void esvg::Path::abstractCloseSubpath(agg::path_storage& _path) {
	_path.end_poly(agg::path_flags_close);
}

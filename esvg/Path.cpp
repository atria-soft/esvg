/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Path.h>
#include <esvg/render/PointList.h>
#include <esvg/render/Weight.h>

esvg::Path::Path(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Path::~Path() {
	
}


// return the next char position ... (after 'X' or NULL)
const char * extractCmd(const char* _input, char& _cmd, std::vector<float>& _outputList) {
	if (*_input == '\0') {
		return nullptr;
	}
	_outputList.clear();
	_cmd = '\0';
	const char * outputPointer = nullptr;
	if (!(    (    _input[0] <= 'Z'
	            && _input[0] >= 'A')
	       || (    _input[0] <= 'z'
	            && _input[0] >= 'a') ) ) {
		ESVG_ERROR("Error in the SVG Path : \"" << _input << "\"");
		return nullptr;
	}
	_cmd = _input[0];
	ESVG_VERBOSE("Find command : " << _cmd);
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
		ESVG_VERBOSE("Find element : " << element);
		_outputList.push_back(element);
		iii += nbElementRead;
	}
	outputPointer = &_input[iii];
	while(*outputPointer!= '\0' && *outputPointer == ' ') {
		outputPointer++;
	}
	//outputPointer++;
	return outputPointer;
}
std::string cleanBadSpaces(const std::string& _input) {
	std::string out;
	bool haveSpace = false;
	for (auto &it : _input) {
		if (    it == ' '
		     || it == '\t'
		     || it == '\t'
		     || it == '\r') {
			haveSpace = true;
		} else {
			if (haveSpace == true) {
				haveSpace = false;
				out += ' ';
			}
			out += it;
		}
	}
	return out;
}

bool esvg::Path::parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	
	std::string elementXML1 = _element.attributes["d"];
	if (elementXML1.size() == 0) {
		ESVG_WARNING("(l "<<_element.getPos()<<") path: missing 'd' attribute or empty");
		return false;
	}
	ESVG_VERBOSE("Parse Path : \"" << elementXML1 << "\"");
	
	char command;
	std::vector<float> listDot;
	elementXML1 = cleanBadSpaces(elementXML1);
	const char* elementXML = elementXML1.c_str();
	
	for( const char *sss=extractCmd(elementXML, command, listDot);
	     sss != nullptr;
	     sss=extractCmd(sss, command, listDot) ) {
		bool relative = false;
		switch(command) {
			case 'm': // Move to (relative)
				relative = true;
			case 'M': // Move to (absolute)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				if (listDot.size() >= 2) {
					m_listElement.moveTo(relative,
					                     vec2(listDot[0], listDot[1]));
				}
				for(int32_t iii=2; iii<listDot.size(); iii+=2) {
					m_listElement.lineTo(relative,
					                     vec2(listDot[iii], listDot[iii+1]));
				}
				break;
			case 'l': // Line to (relative)
				relative = true;
			case 'L': // Line to (absolute)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=2) {
					m_listElement.lineTo(relative,
					                     vec2(listDot[iii], listDot[iii+1]));
				}
				break;
				
			case 'v': // Vertical Line to (relative)
				relative = true;
			case 'V': // Vertical Line to (absolute)
				// 1 Element ...
				if(listDot.size() == 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=1) {
					m_listElement.lineToV(relative,
					                      listDot[iii]);
				}
				break;
				
			case 'h': // Horizantal Line to (relative)
				relative = true;
			case 'H': // Horizantal Line to (absolute)
				// 1 Element ...
				if(listDot.size() == 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=1) {
					m_listElement.lineToH(relative,
					                      listDot[iii]);
				}
				break;
				
			case 'q': // Quadratic Bezier curve (relative)
				relative = true;
			case 'Q': // Quadratic Bezier curve (absolute)
				// 4 Elements ...
				if(listDot.size()%4 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					m_listElement.bezierCurveTo(relative,
					                            vec2(listDot[iii],listDot[iii+1]),
					                            vec2(listDot[iii+2],listDot[iii+3]));
				}
				break;
				
			case 't': // smooth quadratic Bezier curve to (relative)
				relative = true;
			case 'T': // smooth quadratic Bezier curve to (absolute)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=2) {
					m_listElement.bezierSmoothCurveTo(relative,
					                                  vec2(listDot[iii],listDot[iii+1]));
				}
				break;
				
			case 'c': // curve to (relative)
				relative = true;
			case 'C': // curve to (absolute)
				// 6 Elements ...
				if(listDot.size()%6 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=6) {
					m_listElement.curveTo(relative,
					                      vec2(listDot[iii],listDot[iii+1]),
					                      vec2(listDot[iii+2],listDot[iii+3]),
					                      vec2(listDot[iii+4],listDot[iii+5]));
				}
				break;
				
			case 's': // smooth curve to (relative)
				relative = true;
			case 'S': // smooth curve to (absolute)
				// 4 Elements ...
				if(listDot.size()%4 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					m_listElement.smoothCurveTo(relative,
					                            vec2(listDot[iii],listDot[iii+1]),
					                            vec2(listDot[iii+2],listDot[iii+3]));
				}
				break;
				
			case 'a': // elliptical Arc (relative)
				relative = true;
			case 'A': // elliptical Arc (absolute)
				// 7 Elements ...
				if(listDot.size()%7 != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=7) {
					bool largeArcFlag = true;
					bool sweepFlag = true;
					if (listDot[iii+3] == 0.0f) {
						largeArcFlag = false;
					}
					if (listDot[iii+4] == 0.0f) {
						sweepFlag = false;
					}
					m_listElement.ellipticTo(relative,
					                         vec2(listDot[iii], listDot[iii+1]),
					                         listDot[iii+2],
					                         largeArcFlag,
					                         sweepFlag,
					                         vec2(listDot[iii+5], listDot[iii+6]) );
				}
				break;
			case 'z': // closepath (relative)
				relative = true;
			case 'Z': // closepath (absolute)
				// 0 Element ...
				if(listDot.size() != 0) {
					ESVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				m_listElement.close(relative);
				break;
			default:
				ESVG_ERROR ("Unknow error : \"" << command << "\"");
		}
	}
	
	return true;
}

void esvg::Path::display(int32_t _spacing) {
	m_listElement.display(_spacing);
}

void esvg::Path::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Path");
	
	mat2 mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	esvg::render::PointList listPoints;
	listPoints = m_listElement.generateListPoints(_level,
	                                              _myRenderer.getInterpolationRecurtionMax(),
	                                              _myRenderer.getInterpolationThreshold());
	//listPoints.applyMatrix(mtx);
	esvg::render::SegmentList listSegmentFill;
	esvg::render::SegmentList listSegmentStroke;
	esvg::render::Weight tmpFill;
	esvg::render::Weight tmpStroke;
	ememory::SharedPtr<esvg::render::DynamicColor> colorFill = esvg::render::createColor(m_paint.fill, mtx);
	ememory::SharedPtr<esvg::render::DynamicColor> colorStroke;
	if (m_paint.strokeWidth > 0.0f) {
		colorStroke = esvg::render::createColor(m_paint.stroke, mtx);
	}
	// Check if we need to display background
	if (colorFill != nullptr) {
		listSegmentFill.createSegmentList(listPoints);
		colorFill->setViewPort(listSegmentFill.getViewPort());
		listSegmentFill.applyMatrix(mtx);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpFill.generate(_myRenderer.getSize(), _myRenderer.getNumberSubScanLine(), listSegmentFill);
	}
	// check if we need to display stroke:
	if (colorStroke != nullptr) {
		listSegmentStroke.createSegmentListStroke(listPoints,
		                                          m_paint.strokeWidth,
		                                          m_paint.lineCap,
		                                          m_paint.lineJoin,
		                                          m_paint.miterLimit);
		colorStroke->setViewPort(listSegmentStroke.getViewPort());
		listSegmentStroke.applyMatrix(mtx);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpStroke.generate(_myRenderer.getSize(), _myRenderer.getNumberSubScanLine(), listSegmentStroke);
	}
	// add on images:
	_myRenderer.print(tmpFill,
	                  colorFill,
	                  tmpStroke,
	                  colorStroke,
	                  m_paint.opacity);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
		m_listElement.m_debugInformation.applyMatrix(mtx);
		_myRenderer.addDebugSegment(m_listElement.m_debugInformation);
	#endif
}


void esvg::Path::drawShapePoints(std::vector<std::vector<vec2>>& _out,
                                 int32_t _recurtionMax,
                                 float _threshold,
                                 mat2& _basicTrans,
                                 int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW Shape esvg::Path");
	
	mat2 mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	esvg::render::PointList listPoints;
	listPoints = m_listElement.generateListPoints(_level, _recurtionMax, _threshold);
	
	for (auto &it : listPoints.m_data) {
		std::vector<vec2> listPoint;
		for (auto &itDot : it) {
			listPoint.push_back(itDot.m_pos);
		}
		_out.push_back(listPoint);
	}
}


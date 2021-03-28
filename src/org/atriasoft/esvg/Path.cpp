/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Path.hpp>
#include <esvg/render/PointList.hpp>
#include <esvg/render/Weight.hpp>

esvg::Path::Path(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Path::~Path() {
	
}


// return the next char position ... (after 'X' or NULL)
const char * extractCmd(const char* _input, char& _cmd, List<float>& _outputList) {
	if (*_input == '\0') {
		return null;
	}
	_outputList.clear();
	_cmd = '\0';
	const char * outputPointer = null;
	if (!(    (    _input[0] <= 'Z'
	            && _input[0] >= 'A')
	       || (    _input[0] <= 'z'
	            && _input[0] >= 'a') ) ) {
		Log.error("Error in the SVG Path : \"" << _input << "\"");
		return null;
	}
	_cmd = _input[0];
	Log.verbose("Find command : " << _cmd);
	if (_input[1] == '\0') {
		return &_input[1];
	}
	int iii=1;
	// extract every float separated by a ' ' or a ','
	float element;
	char spacer[10];
	int nbElementRead;
	while(    sscanf(&_input[iii], "%1[, ]%f%n", spacer, &element, &nbElementRead) == 2
	       || sscanf(&_input[iii], "%f%n", &element, &nbElementRead) == 1) {
		Log.verbose("Find element : " << element);
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
etk::String cleanBadSpaces(const etk::String& _input) {
	etk::String out;
	boolean haveSpace = false;
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

boolean esvg::Path::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	
	etk::String elementXML1 = _element.attributes["d"];
	if (elementXML1.size() == 0) {
		Log.warning("(l "<<_element.getPos()<<") path: missing 'd' attribute or empty");
		return false;
	}
	Log.verbose("Parse Path : \"" << elementXML1 << "\"");
	
	char command;
	List<float> listDot;
	elementXML1 = cleanBadSpaces(elementXML1);
	const char* elementXML = elementXML1.c_str();
	
	for( const char *sss=extractCmd(elementXML, command, listDot);
	     sss != null;
	     sss=extractCmd(sss, command, listDot) ) {
		boolean relative = false;
		switch(command) {
			case 'm': // Move to (relative)
				relative = true;
			case 'M': // Move to (absolute)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				if (listDot.size() >= 2) {
					this.listElement.moveTo(relative,
					                     Vector2f(listDot[0], listDot[1]));
				}
				for (size_t iii=2; iii<listDot.size(); iii+=2) {
					this.listElement.lineTo(relative,
					                     Vector2f(listDot[iii], listDot[iii+1]));
				}
				break;
			case 'l': // Line to (relative)
				relative = true;
			case 'L': // Line to (absolute)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=2) {
					this.listElement.lineTo(relative,
					                     Vector2f(listDot[iii], listDot[iii+1]));
				}
				break;
				
			case 'v': // Vertical Line to (relative)
				relative = true;
			case 'V': // Vertical Line to (absolute)
				// 1 Element ...
				if(listDot.size() == 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=1) {
					this.listElement.lineToV(relative,
					                      listDot[iii]);
				}
				break;
				
			case 'h': // Horizantal Line to (relative)
				relative = true;
			case 'H': // Horizantal Line to (absolute)
				// 1 Element ...
				if (listDot.size() == 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=1) {
					this.listElement.lineToH(relative,
					                      listDot[iii]);
				}
				break;
				
			case 'q': // Quadratic Bezier curve (relative)
				relative = true;
			case 'Q': // Quadratic Bezier curve (absolute)
				// 4 Elements ...
				if (listDot.size()%4 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=4) {
					this.listElement.bezierCurveTo(relative,
					                            Vector2f(listDot[iii],listDot[iii+1]),
					                            Vector2f(listDot[iii+2],listDot[iii+3]));
				}
				break;
				
			case 't': // smooth quadratic Bezier curve to (relative)
				relative = true;
			case 'T': // smooth quadratic Bezier curve to (absolute)
				// 2 Elements ...
				if (listDot.size()%2 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=2) {
					this.listElement.bezierSmoothCurveTo(relative,
					                                  Vector2f(listDot[iii],listDot[iii+1]));
				}
				break;
				
			case 'c': // curve to (relative)
				relative = true;
			case 'C': // curve to (absolute)
				// 6 Elements ...
				if (listDot.size()%6 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=6) {
					this.listElement.curveTo(relative,
					                      Vector2f(listDot[iii],listDot[iii+1]),
					                      Vector2f(listDot[iii+2],listDot[iii+3]),
					                      Vector2f(listDot[iii+4],listDot[iii+5]));
				}
				break;
				
			case 's': // smooth curve to (relative)
				relative = true;
			case 'S': // smooth curve to (absolute)
				// 4 Elements ...
				if (listDot.size()%4 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=4) {
					this.listElement.smoothCurveTo(relative,
					                            Vector2f(listDot[iii],listDot[iii+1]),
					                            Vector2f(listDot[iii+2],listDot[iii+3]));
				}
				break;
				
			case 'a': // elliptical Arc (relative)
				relative = true;
			case 'A': // elliptical Arc (absolute)
				// 7 Elements ...
				if (listDot.size()%7 != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for (size_t iii=0; iii<listDot.size(); iii+=7) {
					boolean largeArcFlag = true;
					boolean sweepFlag = true;
					if (listDot[iii+3] == 0.0f) {
						largeArcFlag = false;
					}
					if (listDot[iii+4] == 0.0f) {
						sweepFlag = false;
					}
					this.listElement.ellipticTo(relative,
					                         Vector2f(listDot[iii], listDot[iii+1]),
					                         listDot[iii+2],
					                         largeArcFlag,
					                         sweepFlag,
					                         Vector2f(listDot[iii+5], listDot[iii+6]) );
				}
				break;
			case 'z': // closepath (relative)
				relative = true;
			case 'Z': // closepath (absolute)
				// 0 Element ...
				if (listDot.size() != 0) {
					Log.warning("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				this.listElement.close(relative);
				break;
			default:
				ESVG_ERROR ("Unknow error : \"" << command << "\"");
		}
	}
	
	return true;
}

void esvg::Path::display(int _spacing) {
	this.listElement.display(_spacing);
}

void esvg::Path::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::Path");
	
	mat2x3 mtx = this.transformMatrix;
	mtx *= _basicTrans;
	
	esvg::render::PointList listPoints;
	listPoints = this.listElement.generateListPoints(_level,
	                                              _myRenderer.getInterpolationRecurtionMax(),
	                                              _myRenderer.getInterpolationThreshold());
	//listPoints.applyMatrix(mtx);
	esvg::render::SegmentList listSegmentFill;
	esvg::render::SegmentList listSegmentStroke;
	esvg::render::Weight tmpFill;
	esvg::render::Weight tmpStroke;
	ememory::SharedPtr<esvg::render::DynamicColor> colorFill = esvg::render::createColor(this.paint.fill, mtx);
	ememory::SharedPtr<esvg::render::DynamicColor> colorStroke;
	if (this.paint.strokeWidth > 0.0f) {
		colorStroke = esvg::render::createColor(this.paint.stroke, mtx);
	}
	// Check if we need to display background
	if (colorFill != null) {
		listSegmentFill.createSegmentList(listPoints);
		colorFill->setViewPort(listSegmentFill.getViewPort());
		listSegmentFill.applyMatrix(mtx);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpFill.generate(_myRenderer.getSize(), _myRenderer.getNumberSubScanLine(), listSegmentFill);
	}
	// check if we need to display stroke:
	if (colorStroke != null) {
		listSegmentStroke.createSegmentListStroke(listPoints,
		                                          this.paint.strokeWidth,
		                                          this.paint.lineCap,
		                                          this.paint.lineJoin,
		                                          this.paint.miterLimit);
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
	                  this.paint.opacity);
	#ifdef DEBUG
		_myRenderer.addDebugSegment(listSegmentFill);
		_myRenderer.addDebugSegment(listSegmentStroke);
		this.listElement.this.debugInformation.applyMatrix(mtx);
		_myRenderer.addDebugSegment(this.listElement.this.debugInformation);
	#endif
}


void esvg::Path::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                 int _recurtionMax,
                                 float _threshold,
                                 mat2x3& _basicTrans,
                                 int _level) {
	Log.verbose(spacingDist(_level) << "DRAW Shape esvg::Path");
	
	mat2x3 mtx = this.transformMatrix;
	mtx *= _basicTrans;
	
	esvg::render::PointList listPoints;
	listPoints = this.listElement.generateListPoints(_level, _recurtionMax, _threshold);
	listPoints.applyMatrix(mtx);
	for (auto &it : listPoints.this.data) {
		List<Vector2f> listPoint;
		for (auto &itDot : it) {
			listPoint.pushBack(itDot.this.pos);
		}
		_out.pushBack(listPoint);
	}
}


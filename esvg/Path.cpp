/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Path.h>

#undef __class__
#define __class__	"Path"

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
		SVG_ERROR("Error in the SVG Path : \"" << _input << "\"");
		return nullptr;
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

bool esvg::Path::parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element == nullptr) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	
	std::string elementXML1 = _element->getAttribute("d");
	if (elementXML1.size() == 0) {
		SVG_ERROR("(l "<<_element->getPos()<<") path: missing 'p' attribute");
		return false;
	}
	SVG_VERBOSE("Parse Path : \"" << elementXML1 << "\"");
	
	char command;
	std::vector<float> listDot;
	
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
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
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					m_listElement.smoothCurveTo(relative, vec2(listDot[iii],listDot[iii+1]), vec2(listDot[iii+2],listDot[iii+3]));
				}
				break;
				
			case 'a': // elliptical Arc (relative)
				relative = true;
			case 'A': // elliptical Arc (absolute)
				// 7 Elements ...
				if(listDot.size()%7 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				for(int32_t iii=0; iii<listDot.size(); iii+=7) {
					m_listElement.ellipticTo(relative,
					                         listDot[iii],
					                         listDot[iii+1],
					                         listDot[iii+2],
					                         listDot[iii+3],
					                         listDot[iii+4],
					                         listDot[iii+5],
					                         listDot[iii+6]);
				}
				break;
			case 'z': // closepath (relative)
				relative = true;
			case 'Z': // closepath (absolute)
				// 0 Element ...
				if(listDot.size() != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				m_listElement.stop(relative);
				break;
			default:
				SVG_ERROR ("Unknow error : \"" << command << "\"");
		}
	}
	
	return true;
}

void esvg::Path::display(int32_t _spacing) {
	m_listElement.display(_spacing);
}

class Segment {
	public:
		Segment(const vec2& _p0, const vec2& _p1) {
			// segment register all time the lower at P0n then we need to register the sens of the path
			if (_p0.y() < _p1.y()) {
				p0 = _p0;
				p1 = _p1;
				direction = 1.0f; // direction like clock
			} else {
				p0 = _p1;
				p1 = _p0;
				direction = -1.0f; // direction like anti-clock
			}
		}
		vec2 p0;
		vec2 p1;
		float direction;
};


class Scanline {
	private:
		std::vector<float> m_data;
	public:
		// constructor :
		Scanline(size_t _size=32) {
			float tmp(0);
			m_data.resize(_size, tmp);
		}
		// destructor
		~Scanline() { };
	// -----------------------------------------------
	// -- basic tools :
	// -----------------------------------------------
	public:
		size_t size() const {
			return m_data.size();
		};
		void clear(float _fill) {
			for (auto &it : m_data) {
				it = _fill;
			}
		}
		float get(int32_t _pos) const {
			if(    _pos>=0
			    && _pos<m_data.size()) {
				return m_data[_pos];
			}
			return 0;
		}
		void set(int32_t _pos, float _newColor) {
			if(    _pos>=0
			    && _pos<m_data.size()) {
				m_data[_pos] = _newColor;
			}
		}
};

class Weighter {
	private:
		ivec2 m_size;
		std::vector<float> m_data;
	public:
		// constructor :
		Weighter(const ivec2& _size=ivec2(32,32)):
		  m_size(_size) {
			float tmp(0);
			m_data.resize(m_size.x()*m_size.y(), tmp);
			if ((uint32_t)m_size.x()*m_size.y() > m_data.size()) {
				return;
			}
		}
		// destructor
		~Weighter() { };
	// -----------------------------------------------
	// -- basic tools :
	// -----------------------------------------------
	public:
		const ivec2& getSize() const {
			return m_size;
		};
		int32_t getWidth() const {
			return m_size.x();
		};
		int32_t getHeight() const {
			return m_size.y();
		};
		void clear(float _fill) {
			for (int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
				m_data[iii] = _fill;
			}
		}
		float get(const ivec2& _pos) const {
			if (    _pos.x()>0 && _pos.x()<m_size.x()
			     && _pos.y()>0 && _pos.y()<m_size.y()) {
				return m_data[_pos.x()+_pos.y()*m_size.x()];
			}
			return 0;
		}
		void set(const ivec2& _pos, float _newColor) {
			if (    _pos.x()>=0 && _pos.x()<m_size.x()
			     && _pos.y()>=0 && _pos.y()<m_size.y()) {
				m_data[_pos.x()+_pos.y()*m_size.x()] = _newColor;
			}
		}
		void set(int32_t _posY, const Scanline& _data) {
			if (    _posY>=0
			     && _posY<m_size.y()) {
				for (size_t xxx=0; xxx<m_size.x(); ++xxx) {
					m_data[xxx+_posY*m_size.x()] = _data.get(xxx);
				}
			}
		}
		void append(int32_t _posY, const Scanline& _data) {
			if (    _posY>=0
			     && _posY<m_size.y()) {
				for (size_t xxx=0; xxx<m_size.x(); ++xxx) {
					m_data[xxx+_posY*m_size.x()] += _data.get(xxx);
				}
			}
		}
};

bool sortSegmentFunction(const Segment& _e1, const Segment& _e2) {
	return _e1.p0.y() < _e2.p0.y();
}

bool sortXPosFunction(const std::pair<float,float>& _e1, const std::pair<float,float>& _e2) {
	return _e1.first < _e2.first;
}


void addSegment(std::vector<Segment>& _seg, const esvg::render::Point& _pos0, const esvg::render::Point& _pos1) {
	// Skip horizontal Segments
	if (_pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	_seg.push_back(Segment(_pos0.m_pos, _pos1.m_pos));
}

std::vector<Segment> createSegmentList(const std::vector<esvg::render::Point>& _listPoint) {
	std::vector<Segment> out;
	// Build Segments
	for (int32_t iii=0, jjj=_listPoint.size()-1;
	     iii < _listPoint.size();
	     jjj = iii++) {
		addSegment(out, _listPoint[jjj], _listPoint[iii]);
	}
	// TODO : Check if it is really usefull ...
	std::sort(out.begin(), out.end(), sortSegmentFunction);
	return out;
}

std::vector<Segment> createSegmentListStroke(std::vector<esvg::render::Point>& _listPoint) {
	std::vector<Segment> out;
	
	// generate for every point all the orthogonal elements
	//     normal edge             *                 end path                            
	//                           * | *                      * * * * * * * * * * * * *    
	//                         *   |<--*----this                            |       *    
	//                       *     |     *                          this -->|       *    
	//                     *       *       *                                |       *    
	//                   *       . | .       *              . . . . . . . . *       *    
	//                 *       .   |   .       *                            |       *    
	//               *     A .     |     . B     *                          |       *    
	//                     .       *       .                                |       *    
	//                   .       *   *       .              * * * * * * * * * * * * *    
	//                         *       *                                                 
	//                       *           *                                               
	// TODO : Start and stop of the path ...
	for (int32_t idPevious=-1, idCurrent=0, idNext=1;
	     idCurrent < _listPoint.size();
	     idPevious++, idCurrent++, idNext++) {
		if (    _listPoint[idCurrent].m_type == esvg::render::Point::type_join
		     || _listPoint[idCurrent].m_type == esvg::render::Point::type_interpolation) {
			if (idPevious < 0 ) {
				SVG_ERROR("an error occure a previous ID is < 0.... ");
				continue;
			}
			if (idNext >= _listPoint.size()) {
				SVG_ERROR("an error occure a next ID is >= nbPoint len .... ");
				continue;
			}
			vec2 vecA = _listPoint[idCurrent].m_pos - _listPoint[idPevious].m_pos;
			vecA.safeNormalize();
			vec2 vecB = _listPoint[idNext].m_pos - _listPoint[idCurrent].m_pos;
			vecB.safeNormalize();
			vec2 vecC = vecA - vecB;
			if (vecC == vec2(0,0)) {
				// special case: 1 line ...
				_listPoint[idCurrent].m_miterAxe = vec2(vecA.y(), vecA.x());
			} else {
				vecC.safeNormalize();
				_listPoint[idCurrent].m_miterAxe = vecC;
			}
		} else if (_listPoint[idCurrent].m_type == esvg::render::Point::type_start) {
			vec2 vecB = _listPoint[idNext].m_pos - _listPoint[idCurrent].m_pos;
			vecB.safeNormalize();
			_listPoint[idCurrent].m_miterAxe = vec2(vecB.y(), vecB.x());
		} else if (_listPoint[idCurrent].m_type == esvg::render::Point::type_stop) {
			if (idPevious < 0 ) {
				SVG_ERROR("an error occure a previous ID is < 0.... ");
				continue;
			}
			vec2 vecA = _listPoint[idCurrent].m_pos - _listPoint[idPevious].m_pos;
			vecA.safeNormalize();
			_listPoint[idCurrent].m_miterAxe = vec2(vecA.y(), vecA.x());
		} else {
			SVG_TODO("lklklklklkl");
		}
	}
	float lineWidth = 5.0f;
	// create segment list:
	bool haveStartLine;
	vec2 leftPoint;
	vec2 rightPoint;
	for (int32_t iii=0;
	     iii < _listPoint.size();
	     ++iii) {
		switch (_listPoint[iii].m_type) {
			case esvg::render::Point::type_single:
				// just do nothing ....
				SVG_VERBOSE("[" << iii << "] Find Single " << _listPoint[iii].m_pos);
				break;
			case esvg::render::Point::type_start:
				{
					SVG_VERBOSE("[" << iii << "] Find Start " << _listPoint[iii].m_pos);
					if (haveStartLine == true) {
						// close previous :
						SVG_WARNING(" find a non close path ...");
						addSegment(out, leftPoint, rightPoint);
					}
					haveStartLine = true;
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					leftPoint =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					rightPoint =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					addSegment(out, leftPoint, rightPoint);
					SVG_VERBOSE("    segment :" << leftPoint << " -> " << rightPoint);
				}
				break;
			case esvg::render::Point::type_stop:
				{
					SVG_VERBOSE("[" << iii << "] Find Stop " << _listPoint[iii].m_pos);
					if (haveStartLine == true) {
						SVG_WARNING("find close path without start part ...");
						break;
					}
					haveStartLine = false;
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					vec2 left =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					vec2 right =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					//Draw from previous point:
					addSegment(out, leftPoint, left);
					SVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
					addSegment(out, right, rightPoint);
					SVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
					leftPoint = left;
					rightPoint = right;
					// end line ...
					addSegment(out, rightPoint, leftPoint);
					SVG_VERBOSE("    segment :" << rightPoint << " -> " << leftPoint);
				}
				break;
			case esvg::render::Point::type_interpolation:
				{
					SVG_VERBOSE("[" << iii << "] Find interpolation " << _listPoint[iii].m_pos);
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					vec2 left =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					vec2 right =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					//Draw from previous point:
					addSegment(out, leftPoint, left);
					SVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
					addSegment(out, right, rightPoint);
					SVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
					leftPoint = left;
					rightPoint = right;
				}
				break;
			case esvg::render::Point::type_join:
				{
					SVG_VERBOSE("[" << iii << "] Find Join " << _listPoint[iii].m_pos);
					// TODO : Calculate intersection ...  (now we do a simple fast test of path display ...)
					vec2 left =   _listPoint[iii].m_pos
					            + _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					vec2 right =   _listPoint[iii].m_pos
					             - _listPoint[iii].m_miterAxe*lineWidth*0.5f;
					//Draw from previous point:
					addSegment(out, leftPoint, left);
					SVG_VERBOSE("    segment :" << leftPoint << " -> " << left);
					addSegment(out, right, rightPoint);
					SVG_VERBOSE("    segment :" << right << " -> " << rightPoint);
					leftPoint = left;
					rightPoint = right;
				}
				break;
		}
	}
	// TODO : Check if it is really usefull ...
	std::sort(out.begin(), out.end(), sortSegmentFunction);
	return out;
}


Weighter createWeighter(ivec2 _size, int32_t _subSamplingCount, const std::vector<Segment>& _listSegment) {
	Weighter out(_size);
	// for each lines:
	for (int32_t yyy=0; yyy<_size.y(); ++yyy) {
		// Reduce the number of lines in the subsampling parsing:
		std::vector<Segment> availlableSegmentPixel;
		for (auto &it : _listSegment) {
			if (    it.p0.y() <= float(yyy+1)
			     && it.p1.y() >= float(yyy)) {
				availlableSegmentPixel.push_back(it);
			}
		}
		// This represent the pondaration on the subSampling
		float deltaSize = 1.0f/_subSamplingCount;
		for (int32_t kkk=0; kkk<_subSamplingCount ; ++kkk) {
			Scanline scanline(_size.x());
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + deltaSize*0.5f + deltaSize*kkk;
			std::vector<Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    it.p0.y() <= subSamplingCenterPos
				     && it.p1.y() >= subSamplingCenterPos) {
					availlableSegment.push_back(it);
				}
			}
			// x position, angle
			std::vector<std::pair<float, float>> listPosition;
			for (auto &it : availlableSegment) {
				vec2 delta = it.p0 - it.p1;
				// x = coefficent*y+bbb;
				float coefficient = delta.x()/delta.y();
				float bbb = it.p0.x() - coefficient*it.p0.y();
				float xpos = coefficient * subSamplingCenterPos + bbb;
				listPosition.push_back(std::pair<float,float>(xpos, it.direction));
			}
			// now we order position of the xPosition:
			std::sort(listPosition.begin(), listPosition.end(), sortXPosFunction);
			// move through all element in the point:
			float lastState = 0.0f;
			float currentValue = 0.0f;
			int32_t lastPos = -1;
			int32_t currentPos = -1;
			float lastX = 0.0f;
			// *      |                \---------------/              |
			// * current pos
			//                         * pos ...
			// TODO : Code the Odd/even and non-zero ...
			for (auto &it : listPosition) {
				if (currentPos != int32_t(it.first)) {
					// fill to the new pos -1:
					float endValue = std::min(1.0f,std::abs(lastState)) * deltaSize;
					for (int32_t iii=currentPos+1; iii<int32_t(it.first); ++iii) {
						scanline.set(iii, endValue);
					}
					currentPos = int32_t(it.first);
					currentValue = endValue;
				}
				float oldState = lastState;
				lastState += it.second;
				if (oldState == 0.0f) {
					// nothing to draw before ...
					float ratio = 1.0f - (it.first - float(int32_t(it.first)));
					currentValue += ratio * deltaSize;
				} else if (lastState == 0.0f) {
					// something new to draw ...
					float ratio = 1.0f - (it.first - float(int32_t(it.first)));
					currentValue -= ratio * deltaSize;
				} else {
					// nothing to do ...
				}
				
				if (currentPos == int32_t(it.first)) {
					scanline.set(currentPos, currentValue);
				}
			}
			out.append(yyy, scanline);
		}
	}
	return out;
}



void esvg::Path::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Path");
	int32_t recurtionMax = 10;
	float threshold = 0.25f;
	std::vector<esvg::render::Point> listPoints = m_listElement.generateListPoints(_level, recurtionMax, threshold);
	
	mat2 mtx = m_transformMatrix;
	mtx *= _basicTrans;
	Weighter tmpFill;
	Weighter tmpStroke;
	// Check if we need to display background
	int32_t nbSubScanLine = 8;
	if (m_paint.fill.a() != 0x00) {
	
		std::vector<Segment> listSegment = createSegmentList(listPoints);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpFill = createWeighter(ivec2(128,128), nbSubScanLine, listSegment);
	}
	// check if we need to display stroke:
	if (    m_paint.strokeWidth > 0
	     && m_paint.stroke.a() != 0x00) {
		std::vector<Segment> listSegment = createSegmentListStroke(listPoints);
		// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
		tmpStroke = createWeighter(ivec2(128,128), nbSubScanLine, listSegment);
	}
	// add on images:
	for (int32_t yyy=0; yyy<_myRenderer.m_size.y(); ++yyy) {
		for (int32_t xxx=0; xxx<_myRenderer.m_size.x(); ++xxx) {
			ivec2 pos(xxx, yyy);
			float value = tmpFill.get(pos);
			float valueStroke = tmpStroke.get(pos);
			if (valueStroke != 0.0f) {
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4    ] = uint8_t(valueStroke*m_paint.stroke.r());
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4 + 1] = uint8_t(valueStroke*m_paint.stroke.g());
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4 + 2] = uint8_t(valueStroke*m_paint.stroke.b());
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4 + 3] = uint8_t(valueStroke*m_paint.stroke.a());
			} else {
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4    ] = uint8_t(value*m_paint.fill.r());
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4 + 1] = uint8_t(value*m_paint.fill.g());
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4 + 2] = uint8_t(value*m_paint.fill.b());
				_myRenderer.m_buffer[(_myRenderer.m_size.x()*yyy + xxx)*4 + 3] = uint8_t(value*m_paint.fill.a());
			}
		}
	}
}


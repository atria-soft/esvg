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
				pathElement.m_cmd = esvg::path_moveTo;
				if (listDot.size() >= 2) {
					pathElement.m_element[0] = listDot[0];
					pathElement.m_element[1] = listDot[1];
					m_listElement.push_back(pathElement);
				}
				pathElement.m_cmd = esvg::path_lineTo;
				for(int32_t iii=2; iii<listDot.size(); iii+=2) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'L': // Line to (absolute)
			case 'l': // Line to (relative)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_lineTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=2) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'V': // Vertical Line to (absolute)
			case 'v': // Vertical Line to (relative)
				// 1 Element ...
				if(listDot.size() == 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_lineToV;
				for(int32_t iii=0; iii<listDot.size(); iii+=1) {
					pathElement.m_element[0] = listDot[iii];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'H': // Horizantal Line to (absolute)
			case 'h': // Horizantal Line to (relative)
				// 1 Element ...
				if(listDot.size() == 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_lineToH;
				for(int32_t iii=0; iii<listDot.size(); iii+=1) {
					pathElement.m_element[0] = listDot[iii];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'Q': // Quadratic Bezier curve (absolute)
			case 'q': // Quadratic Bezier curve (relative)
				// 4 Elements ...
				if(listDot.size()%4 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_bezierCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'T': // smooth quadratic Bezier curve to (absolute)
			case 't': // smooth quadratic Bezier curve to (relative)
				// 2 Elements ...
				if(listDot.size()%2 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_bezierSmothCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=2) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'C': // curve to (absolute)
			case 'c': // curve to (relative)
				// 6 Elements ...
				if(listDot.size()%6 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = path_curveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=6) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					pathElement.m_element[4] = listDot[iii+4];
					pathElement.m_element[5] = listDot[iii+5];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'S': // smooth curve to (absolute)
			case 's': // smooth curve to (relative)
				// 4 Elements ...
				if(listDot.size()%4 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_smothCurveTo;
				for(int32_t iii=0; iii<listDot.size(); iii+=4) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					m_listElement.push_back(pathElement);
				}
				break;
				
			case 'A': // elliptical Arc (absolute)
			case 'a': // elliptical Arc (relative)
				// 7 Elements ...
				if(listDot.size()%7 != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_elliptic;
				for(int32_t iii=0; iii<listDot.size(); iii+=7) {
					pathElement.m_element[0] = listDot[iii];
					pathElement.m_element[1] = listDot[iii+1];
					pathElement.m_element[2] = listDot[iii+2];
					pathElement.m_element[3] = listDot[iii+3];
					pathElement.m_element[4] = listDot[iii+4];
					pathElement.m_element[5] = listDot[iii+5];
					pathElement.m_element[6] = listDot[iii+6];
					m_listElement.push_back(pathElement);
				}
				break;
			case 'Z': // closepath (absolute)
			case 'z': // closepath (relative)
				// 0 Element ...
				if(listDot.size() != 0) {
					SVG_WARNING("the PATH command "<< command << " has not the good number of element = " << listDot.size() );
					break;
				}
				pathElement.m_cmd = esvg::path_stop;
				m_listElement.push_back(pathElement);
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
			case esvg::path_stop:
				SVG_DEBUG(spacingDist(_spacing+4) << "STOP");
				break;
			case esvg::path_moveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "MOVETO (" << m_listElement[iii].m_element[0] << "," << m_listElement[iii].m_element[1] << ")" );
				break;
			case esvg::path_lineTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO (" << m_listElement[iii].m_element[0] << "," << m_listElement[iii].m_element[1] << ")" );
				break;
			case esvg::path_lineToH:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO_H (" << m_listElement[iii].m_element[0] << ")" );
				break;
			case esvg::path_lineToV:
				SVG_DEBUG(spacingDist(_spacing+4) << "LINETO_V (" << m_listElement[iii].m_element[0] << ")" );
				break;
			case esvg::path_curveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "CURVETO (" << m_listElement[iii].m_element[0] << 
				                                             "," << m_listElement[iii].m_element[1] << 
				                                             "," << m_listElement[iii].m_element[2] << 
				                                             "," << m_listElement[iii].m_element[3] << 
				                                             "," << m_listElement[iii].m_element[4] << 
				                                             "," << m_listElement[iii].m_element[5] << ")" );
				break;
			case esvg::path_smothCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "SMOTH_CURVETO (" << m_listElement[iii].m_element[0] <<
				                                                   "," << m_listElement[iii].m_element[1] << 
				                                                   "," << m_listElement[iii].m_element[2] << 
				                                                   "," << m_listElement[iii].m_element[3] <<  ")" );
				break;
			case esvg::path_bezierCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "BEZIER_CURVETO (" << m_listElement[iii].m_element[0] << 
				                                                    "," << m_listElement[iii].m_element[1] << 
				                                                    "," << m_listElement[iii].m_element[2] << 
				                                                    "," << m_listElement[iii].m_element[3] << ")" );
				break;
			case esvg::path_bezierSmothCurveTo:
				SVG_DEBUG(spacingDist(_spacing+4) << "BEZIER_SMOTH_CURVETO (" << m_listElement[iii].m_element[0] << "," << m_listElement[iii].m_element[1] << ")" );
				break;
			case esvg::path_elliptic:
				SVG_DEBUG(spacingDist(_spacing+4) << "ELLIPTIC (" << m_listElement[iii].m_element[0] << 
				                                              "," << m_listElement[iii].m_element[1] << 
				                                              "," << m_listElement[iii].m_element[2] << 
				                                              "," << m_listElement[iii].m_element[3] << 
				                                              "," << m_listElement[iii].m_element[4] << 
				                                              "," << m_listElement[iii].m_element[5] << 
				                                              "," << m_listElement[iii].m_element[6] << ")" );
				// show explanation at : http://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
				break;
			default:
				SVG_DEBUG(spacingDist(_spacing+4) << "????" );
				break;
		}
	}
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

class PointRender {
	public:
		enum typePoint {
			typePoint_single, //!< Point type is single, this mean that it start and stop of a path
			typePoint_start, //!< Point type is starting of a path
			typePoint_stop, //!< Point type is stoping of a path
			typePoint_join, //!< Point type in an user point provided inside a path
			typePoint_interpolation, //!< This point is dynamicly calculated to create an interpolation
		};
	public:
		vec2 m_pos; //!< position of the point
		enum typePoint m_type;
		vec2 m_miterAxe;
		vec2 m_delta;
		float m_len;
		PointRender(const vec2& _pos, enum typePoint _type = PointRender::typePoint_join) :
		  m_pos(_pos),
		  m_type(_type) {
			// nothing to do ...
		}
		void setEndPath() {
			if (m_type == typePoint_interpolation) {
				SVG_WARNING("Request stop path of an interpolate Point");
				m_type = typePoint_stop;
				return;
			}
			if (m_type == typePoint_stop) {
				SVG_WARNING("Request stop path of an STOP Point");
				return;
			}
			if (m_type == typePoint_start) {
				m_type = typePoint_single;
				return;
			}
			m_type = typePoint_stop;
		}
		void normalize(const vec2& _nextPoint) {
			m_delta = _nextPoint - m_pos;
			m_len = m_delta.length();
		}
};

void diplayRenderPoints(const std::vector<PointRender>& listPoints) {
	SVG_VERBOSE(" Display list of points : size=" << listPoints.size());
	for (int32_t iii=0;
	     iii < listPoints.size();
	     ++iii) {
		switch (listPoints[iii].m_type) {
			case PointRender::typePoint_single:
				SVG_VERBOSE("    [" << iii << "] Find Single " << listPoints[iii].m_pos);
				break;
			case PointRender::typePoint_start:
				SVG_VERBOSE("    [" << iii << "] Find Start " << listPoints[iii].m_pos);
				break;
			case PointRender::typePoint_stop:
				SVG_VERBOSE("    [" << iii << "] Find Stop " << listPoints[iii].m_pos);
				break;
			case PointRender::typePoint_interpolation:
				SVG_VERBOSE("    [" << iii << "] Find interpolation " << listPoints[iii].m_pos);
				break;
			case PointRender::typePoint_join:
				SVG_VERBOSE("    [" << iii << "] Find Join " << listPoints[iii].m_pos);
				break;
		}
	}
}

void interpolateCubicBezier(std::vector<PointRender>& _listPoint,
                            int32_t _recurtionMax,
                            float _threshold,
                            vec2 _pos1,
                            vec2 _pos2,
                            vec2 _pos3,
                            vec2 _pos4,
                            int32_t _level,
                            enum PointRender::typePoint _type) {
	if (_level > _recurtionMax) {
		return;
	}
	vec2 pos12 = (_pos1+_pos2)*0.5f;
	vec2 pos23 = (_pos2+_pos3)*0.5f;
	vec2 pos34 = (_pos3+_pos4)*0.5f;
	
	vec2 delta = _pos4 - _pos1;
	float distance2 = std::abs(((_pos2.x() - _pos4.x()) * delta.y() - (_pos2.y() - _pos4.y()) * delta.x() ));
	float distance3 = std::abs(((_pos3.x() - _pos4.x()) * delta.y() - (_pos3.y() - _pos4.y()) * delta.x() ));
	
	if ((distance2 + distance3)*(distance2 + distance3) < _threshold * delta.length2()) {
		_listPoint.push_back(PointRender(_pos4, _type) );
		return;
	}
	vec2 pos123 = (pos12+pos23)*0.5f;
	vec2 pos234 = (pos23+pos34)*0.5f;
	vec2 pos1234 = (pos123+pos234)*0.5f;
	
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, _pos1, pos12, pos123, pos1234, _level+1, PointRender::typePoint_interpolation);
	interpolateCubicBezier(_listPoint, _recurtionMax, _threshold, pos1234, pos234, pos34, _pos4, _level+1, _type);
}

void addSegment(std::vector<Segment>& _seg, const PointRender& _pos0, const PointRender& _pos1) {
	// Skip horizontal Segments
	if (_pos0.m_pos.y() == _pos1.m_pos.y()) {
		// remove /0 operation
		return;
	}
	_seg.push_back(Segment(_pos0.m_pos, _pos1.m_pos));
}

std::vector<Segment> createSegmentList(const std::vector<PointRender>& _listPoint) {
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

std::vector<Segment> createSegmentListStroke(std::vector<PointRender>& _listPoint) {
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
		if (    _listPoint[idCurrent].m_type == PointRender::typePoint_join
		     || _listPoint[idCurrent].m_type == PointRender::typePoint_interpolation) {
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
		} else if (_listPoint[idCurrent].m_type == PointRender::typePoint_start) {
			vec2 vecB = _listPoint[idNext].m_pos - _listPoint[idCurrent].m_pos;
			vecB.safeNormalize();
			_listPoint[idCurrent].m_miterAxe = vec2(vecB.y(), vecB.x());
		} else if (_listPoint[idCurrent].m_type == PointRender::typePoint_stop) {
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
			case PointRender::typePoint_single:
				// just do nothing ....
				SVG_VERBOSE("[" << iii << "] Find Single " << _listPoint[iii].m_pos);
				break;
			case PointRender::typePoint_start:
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
			case PointRender::typePoint_stop:
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
			case PointRender::typePoint_interpolation:
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
			case PointRender::typePoint_join:
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



void esvg::Path::aggDraw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Path");
	vec2 lastPosition(0.0f, 0.0f);
	std::vector<PointRender> listPoints;
	int32_t lastPointId = -1;
	bool PathStart = false;
	int32_t recurtionMax = 10;
	float threshold = 0.25f;
	// Foreach element, we move in the path:
	for(int32_t iii=0; iii<m_listElement.size(); iii++) {
		switch (m_listElement[iii].m_cmd) {
			case esvg::path_stop:
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_stop");
				// TODO : Check if the z value mean that the path will cycle ...
				if (listPoints.size() != 0) {
					if (PathStart == false) {
						SVG_WARNING(spacingDist(_level+1) << "[" << iii << "] Request path stop of not starting path ...");
					} else {
						listPoints.back().setEndPath();
						PathStart = false;
					}
				}
				// nothing alse to do ...
				break;
			case esvg::path_moveTo:
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_moveTo");
				// stop last path
				if (listPoints.size() != 0) {
					if (PathStart == true) {
						listPoints.back().setEndPath();
						PathStart = false;
					}
				}
				PathStart = true;
				// create a new one
				if (m_listElement[iii].m_relative == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += vec2(m_listElement[iii].m_element[0], m_listElement[iii].m_element[1]);
				listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_start));
				break;
			case esvg::path_lineTo:
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_lineTo");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_join));
					PathStart = true;
				}
				if (m_listElement[iii].m_relative == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += vec2(m_listElement[iii].m_element[0], m_listElement[iii].m_element[1]);
				listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_start));
				break;
			case esvg::path_lineToH:
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_lineToH");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_join));
					PathStart = true;
				}
				if (m_listElement[iii].m_relative == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += vec2(m_listElement[iii].m_element[0], 0.0f);
				listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_start));
				break;
			case esvg::path_lineToV:
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_lineToV");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_join));
					PathStart = true;
				}
				if (m_listElement[iii].m_relative == false) {
					lastPosition = vec2(0.0f, 0.0f);
				}
				lastPosition += vec2(0.0, m_listElement[iii].m_element[1]);
				listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_start));
				break;
			case esvg::path_curveTo:
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_curveTo");
				// If no previous point, we need to create the last point has start ...
				if (PathStart == false) {
					listPoints.push_back(PointRender(lastPosition, PointRender::typePoint_join));
					PathStart = true;
				}
				{
					vec2 lastPosStore(lastPosition);
					if (m_listElement[iii].m_relative == false) {
						lastPosition = vec2(0.0f, 0.0f);
					}
					vec2 pos1 = lastPosition + vec2(m_listElement[iii].m_element[0], m_listElement[iii].m_element[1]);
					vec2 pos2 = lastPosition + vec2(m_listElement[iii].m_element[2], m_listElement[iii].m_element[3]);
					vec2 pos = lastPosition + vec2(m_listElement[iii].m_element[4], m_listElement[iii].m_element[5]);
					interpolateCubicBezier(listPoints,
					                       recurtionMax,
					                       threshold,
					                       lastPosStore,
					                       pos1,
					                       pos2,
					                       pos,
					                       0,
					                       PointRender::typePoint_join);
					lastPosition = pos;
				}
				break;
			case esvg::path_smothCurveTo:
				SVG_TODO(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_smothCurveTo");
				/*
				path.curve4SmoothTo(m_listElement[iii].m_relative,
				                    vec2(m_listElement[iii].m_element[0],
				                         m_listElement[iii].m_element[1]),
				                    vec2(m_listElement[iii].m_element[2],
				                         m_listElement[iii].m_element[3]) );
				*/
				break;
			case esvg::path_bezierCurveTo:
				SVG_TODO(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_bezierCurveTo");
				/*
				path.curve3To(m_listElement[iii].m_relative,
				              vec2(m_listElement[iii].m_element[0],
				                   m_listElement[iii].m_element[1]),
				              vec2(m_listElement[iii].m_element[2],
				                   m_listElement[iii].m_element[3]) );
				*/
				break;
			case esvg::path_bezierSmothCurveTo:
				SVG_TODO(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_bezierSmothCurveTo");
				/*
				path.curve3SmoothTo(m_listElement[iii].m_relative,
				                    vec2(m_listElement[iii].m_element[0],
				                         m_listElement[iii].m_element[1]) );
				*/
				break;
			case esvg::path_elliptic:
				/*
				SVG_VERBOSE(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_elliptic");
				path.ellipticTo(m_listElement[iii].m_relative,
				                m_listElement[iii].m_element[0],
				                m_listElement[iii].m_element[1],
				                m_listElement[iii].m_element[2],
				                m_listElement[iii].m_element[3],
				                m_listElement[iii].m_element[4],
				                m_listElement[iii].m_element[5],
				                m_listElement[iii].m_element[6] );
				*/
				SVG_TODO(spacingDist(_level+1) << "[" << iii << "] Draw : esvg::path_elliptic");
				break;
			default:
				SVG_ERROR(spacingDist(_level+1) << "[" << iii << "] Unknow PATH commant (internal error)");
				break;
		}
	}
	diplayRenderPoints(listPoints);
	
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


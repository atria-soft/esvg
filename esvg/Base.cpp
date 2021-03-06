/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <esvg/debug.hpp>
#include <esvg/Base.hpp>
#include <cmath>

const float esvg::kappa90(0.5522847493f);

esvg::PaintState::PaintState() :
  fill(etk::Pair<etk::Color<float,4>, etk::String>(etk::color::black, "")),
  stroke(etk::Pair<etk::Color<float,4>, etk::String>(etk::color::none, "")),
  strokeWidth(1.0f),
  flagEvenOdd(false),
  lineCap(esvg::cap_butt),
  lineJoin(esvg::join_miter),
  miterLimit(4.0f),
  viewPort(vec2(0.0f,0.0f), vec2(0.0f,0.0f)),
  opacity(1.0) {
	
}

void esvg::PaintState::clear() {
	fill = etk::Pair<etk::Color<float,4>, etk::String>(etk::color::black, "");
	stroke = etk::Pair<etk::Color<float,4>, etk::String>(etk::color::none, "");
	strokeWidth = 1.0;
	viewPort.first.setValue(0.0f,0.0f);
	viewPort.first.setValue(0.0f,0.0f);
	flagEvenOdd = false;
	lineJoin = esvg::join_miter;
	lineCap = esvg::cap_butt;
	miterLimit = 4.0f;
	opacity = 1.0;
}


esvg::Base::Base(PaintState _parentPaintState) {
	// copy the parent painting properties ...
	m_paint = _parentPaintState;
}

etk::String extractTransformData(const etk::String& _value, const etk::String& _base) {
	size_t posStart = _value.find(_base);
	if (posStart == etk::String::npos) {
		// Not find element is a normal case ...
		return "";
	}
	posStart += _base.size();
	if (_value.size() < posStart+2) {
		ESVG_ERROR("Not enought spece in the String to have transform value for ' (' or '()' in '" << _value << "'");
		return "";
	}
	if (_value[posStart] == '(') {
		// normal SVG does not support this case ...
		posStart++;
	} else if (    _value[posStart] == ' '
	            && _value[posStart+1] == '(') {
		posStart+=2;
	} else {
		ESVG_ERROR("Can not find ' (' or '(' in '" << &_value[posStart] << "' for '" << _value << "'");
		return "";
	}
	if (_value.size() < posStart+1) {
		ESVG_ERROR("Not enought spece in the String to have transform value for ')' in '" << _value << "'");
		return "";
	}
	size_t posEnd = _value.find(')', posStart);
	if (posEnd == etk::String::npos) {
		ESVG_ERROR("Missing element ')' in '" << _value << "' for " << _base);
		return "";
	}
	ESVG_VERBOSE("Find : '" << etk::String(_value.begin()+posStart, _value.begin()+posEnd) << "' for " << _base);
	return etk::String(_value.begin()+posStart, _value.begin()+posEnd);
}

void esvg::Base::parseTransform(const exml::Element& _element) {
	if (_element.exist() == false) {
		return;
	}
	etk::String inputString = _element.attributes["transform"];
	if (inputString.size() == 0) {
		return;
	}
	ESVG_VERBOSE("find transform : \"" << inputString << "\"");
	for (size_t iii=0; iii<inputString.size(); iii++) {
		if (inputString[iii] == ',') {
			inputString[iii] = ' ';
		}
	}
	ESVG_VERBOSE("find transform : \"" << inputString << "\"");
	// need to find elements in order ...
	etk::String data = extractTransformData(inputString, "matrix");
	if (data.size() != 0) {
		double matrix[6];
		if (sscanf(data.c_str(), "%lf %lf %lf %lf %lf %lf", &matrix[0], &matrix[1], &matrix[2], &matrix[3], &matrix[4], &matrix[5]) == 6) {
			m_transformMatrix = mat2x3(matrix);
			// find a matrix : simply exit ...
			return;
		} else {
			ESVG_ERROR("Parsing matrix() with wrong data ... '" << data << "'");
		}
	}
	data = extractTransformData(inputString, "translate");
	if (data.size() != 0) {
		float xxx, yyy;
		if (sscanf(data.c_str(), "%f %f", &xxx, &yyy) == 2) {
			m_transformMatrix *= etk::mat2x3Translate(vec2(xxx, yyy));
			ESVG_VERBOSE("Translate : " << xxx << ", " << yyy);
		} else if (sscanf(data.c_str(), "%f", &xxx) == 1) {
			m_transformMatrix *= etk::mat2x3Translate(vec2(xxx, 0));
			ESVG_VERBOSE("Translate : " << xxx << ", " << 0);
		} else {
			ESVG_ERROR("Parsing translate() with wrong data ... '" << data << "'");
		}
	}
	data = extractTransformData(inputString, "scale");
	if (data.size() != 0) {
		float xxx, yyy;
		if (sscanf(data.c_str(), "%f %f", &xxx, &yyy) == 2) {
			m_transformMatrix *= etk::mat2x3Scale(vec2(xxx, yyy));
			ESVG_VERBOSE("Scale : " << xxx << ", " << yyy);
		} else if (sscanf(data.c_str(), "%f", &xxx) == 1) {
			m_transformMatrix *= etk::mat2x3Scale(xxx);
			ESVG_VERBOSE("Scale : " << xxx << ", " << xxx);
		} else {
			ESVG_ERROR("Parsing scale() with wrong data ... '" << data << "'");
		}
	}
	data = extractTransformData(inputString, "rotate");
	if (data.size() != 0) {
		float angle, xxx, yyy;
		if (sscanf(data.c_str(), "%f %f %f", &angle, &xxx, &yyy) == 3) {
			angle = angle / 180 * M_PI;
			m_transformMatrix *= etk::mat2x3Translate(vec2(-xxx, -yyy));
			m_transformMatrix *= etk::mat2x3Rotate(angle);
			m_transformMatrix *= etk::mat2x3Translate(vec2(xxx, yyy));
		} else if (sscanf(data.c_str(), "%f", &angle) == 1) {
			angle = angle / 180 * M_PI;
			ESVG_VERBOSE("rotate : " << angle << "rad, " << (angle/M_PI*180) << "°");
			m_transformMatrix *= etk::mat2x3Rotate(angle);
		} else {
			ESVG_ERROR("Parsing rotate() with wrong data ... '" << data << "'");
		}
	}
	data = extractTransformData(inputString, "skewX");
	if (data.size() != 0) {
		float angle;
		if (sscanf(data.c_str(), "%f", &angle) == 1) {
			angle = angle / 180 * M_PI;
			ESVG_VERBOSE("skewX : " << angle << "rad, " << (angle/M_PI*180) << "°");
			m_transformMatrix *= etk::mat2x3Skew(vec2(angle, 0.0f));
		} else {
			ESVG_ERROR("Parsing skewX() with wrong data ... '" << data << "'");
		}
	}
	data = extractTransformData(inputString, "skewY");
	if (data.size() != 0) {
		float angle;
		if (sscanf(data.c_str(), "%f", &angle) == 1) {
			angle = angle / 180 * M_PI;
			ESVG_VERBOSE("skewY : " << angle << "rad, " << (angle/M_PI*180) << "°");
			m_transformMatrix *= etk::mat2x3Skew(vec2(0.0f, angle));
		} else {
			ESVG_ERROR("Parsing skewY() with wrong data ... '" << data << "'");
		}
	}
}

void esvg::Base::parsePosition(const exml::Element& _element, vec2 &_pos, vec2 &_size) {
	_pos.setValue(0,0);
	_size.setValue(0,0);
	
	if (_element.exist() == false) {
		return;
	}
	etk::String content = _element.attributes["x"];
	if (content.size()!=0) {
		_pos.setX(parseLength(content));
	}
	content = _element.attributes["y"];
	if (content.size()!=0) {
		_pos.setY(parseLength(content));
	}
	content = _element.attributes["width"];
	if (content.size()!=0) {
		_size.setX(parseLength(content));
	}
	content = _element.attributes["height"];
	if (content.size()!=0) {
		_size.setY(parseLength(content));
	}
}


etk::Pair<float, enum esvg::distance> esvg::Base::parseLength2(const etk::String& _dataInput) {
	ESVG_VERBOSE(" lenght : '" << _dataInput << "'");
	float n = _dataInput.to<float>();
	etk::String unit;
	for (size_t iii=0; iii<_dataInput.size(); ++iii) {
		if(    (_dataInput[iii]>='0' && _dataInput[iii]<='9')
		    || _dataInput[iii]=='+'
		    || _dataInput[iii]=='-'
		    || _dataInput[iii]=='.') {
			continue;
		}
		unit = etk::String(_dataInput, iii);
		break;
	}
	ESVG_VERBOSE(" lenght : '" << n << "' => unit=" << unit);
	// note : ";" is for the parsing of the style elements ...
	if(unit.size() == 0) {
		return etk::makePair(n, esvg::distance_pixel);
	} else if (unit[0] == '%') {     // xxx %
		return etk::makePair(n, esvg::distance_pourcent);
	} else if (    unit[0] == 'e'
	            && unit[1] == 'm') { // xxx em
		return etk::makePair(n, esvg::distance_element);
	} else if (    unit[0] == 'e'
	            && unit[1] == 'x') { // xxx ex
		return etk::makePair(n, esvg::distance_ex);
	} else if (    unit[0] == 'p'
	            && unit[1] == 'x') { // xxx px
		return etk::makePair(n, esvg::distance_pixel);
	} else if (    unit[0] == 'p'
	            && unit[1] == 't') { // xxx pt
		return etk::makePair(n, esvg::distance_point);
	} else if (    unit[0] == 'p'
	            && unit[1] == 'c') { // xxx pc
		return etk::makePair(n, esvg::distance_pc);
	} else if (    unit[0] == 'm'
	            && unit[1] == 'm') { // xxx mm
		return etk::makePair(n, esvg::distance_millimeter);
	} else if (    unit[0] == 'c'
	            && unit[1] == 'm') { // xxx cm
		return etk::makePair(n, esvg::distance_centimeter);
	} else if (    unit[0] == 'i'
	            && unit[1] == 'n') { // xxx in
		return etk::makePair(n, esvg::distance_inch);
	}
	return etk::makePair(0.0f, esvg::distance_pixel);
}


float esvg::Base::parseLength(const etk::String& _dataInput) {
	etk::Pair<float, enum esvg::distance> value = parseLength2(_dataInput);
	ESVG_VERBOSE(" lenght : '" << value.first << "' => unit=" << value.second);
	float font_size = 20.0f;
	switch (value.second) {
		case esvg::distance_pourcent:
			return value.first;// / 100.0 * m_paint.viewPort.x();
		case esvg::distance_element:
			return value.first * font_size;
		case esvg::distance_ex:
			return value.first / 2.0f * font_size;
		case esvg::distance_pixel:
			return value.first;
		case esvg::distance_point:
			return value.first * 1.25f;
		case esvg::distance_pc:
			return value.first * 15.0f;
		case esvg::distance_millimeter:
			return value.first * 3.543307f;
		case esvg::distance_centimeter:
			return value.first * 35.43307f;
		case esvg::distance_inch:
			return value.first * 90.0f;
	}
	return 0.0f;
}

void esvg::Base::parsePaintAttr(const exml::Element& _element) {
	if (_element.exist() == false) {
		return;
	}
	/*
	bool fillNone = false;
	bool strokeNone = false;
	*/
	etk::String content;
	// ---------------- get unique ID ----------------
	m_id = _element.attributes["id"];
	// ---------------- stroke ----------------
	content = _element.attributes["stroke"];
	if (content == "none") {
		m_paint.stroke = etk::Pair<etk::Color<float,4>, etk::String>(etk::color::none, "");
	} else {
		if (content.size()!=0) {
			m_paint.stroke = parseColor(content);
		}
		content = _element.attributes["stroke-width"];
		if (content.size()!=0) {
			m_paint.strokeWidth = parseLength(content);
		}
		content = _element.attributes["stroke-opacity"];
		if (content.size()!=0) {
			float opacity = parseLength(content);
			opacity = etk::avg(0.0f, opacity, 1.0f);
			m_paint.stroke.first.setA(opacity);
		}
		
		content = _element.attributes["stroke-dasharray"];
		if (content.size()!=0) {
			if (content == "none" ) {
				// OK, Nothing to do ...
			} else {
				ESVG_TODO(" 'stroke-dasharray' not implemented ...");
			}
		}
		content = _element.attributes["stroke-linecap"];
		if (content.size()!=0) {
			if (content == "butt" ) {
				m_paint.lineCap = esvg::cap_butt;
			} else if (content == "round" ) {
				m_paint.lineCap = esvg::cap_round;
			} else if (content == "square" ) {
				m_paint.lineCap = esvg::cap_square;
			} else {
				m_paint.lineCap = esvg::cap_butt;
				ESVG_ERROR("not know stroke-linecap value : \"" << content << "\", not in [butt,round,square]");
			}
		}
		content = _element.attributes["stroke-linejoin"];
		if (content.size()!=0) {
			if (content == "miter" ) {
				m_paint.lineJoin = esvg::join_miter;
			} else if (content == "round" ) {
				m_paint.lineJoin = esvg::join_round;
			} else if (content == "bevel" ) {
				m_paint.lineJoin = esvg::join_bevel;
			} else {
				m_paint.lineJoin = esvg::join_miter;
				ESVG_ERROR("not know stroke-linejoin value : \"" << content << "\", not in [miter,round,bevel]");
			}
		}
		content = _element.attributes["stroke-miterlimit"];
		if (content.size()!=0) {
			float tmp = parseLength(content);
			m_paint.miterLimit = etk::max(0.0f, tmp);
		}
	}
	// ---------------- FILL ----------------
	content = _element.attributes["fill"];
	if (content == "none") {
		m_paint.fill = etk::Pair<etk::Color<float,4>, etk::String>(etk::color::none, "");
	} else {
		if (content.size()!=0) {
			m_paint.fill = parseColor(content);
		}
		content = _element.attributes["fill-opacity"];
		if (content.size()!=0) {
			float opacity = parseLength(content);
			opacity = etk::avg(0.0f, opacity, 1.0f);
			m_paint.fill.first.setA(opacity);
		}
		content = _element.attributes["fill-rule"];
		if (content.size()!=0) {
			if (content == "nonzero") {
				m_paint.flagEvenOdd = false;
			} else if (content == "evenodd" ) {
				m_paint.flagEvenOdd = true;
			} else {
				ESVG_ERROR("not know fill-rule value : \"" << content << "\", not in [nonzero,evenodd]");
			}
		}
		// ---------------- opacity ----------------
		content = _element.attributes["opacity"];
		if (content.size()!=0) {
			m_paint.opacity = parseLength(content);
			m_paint.opacity = etk::avg(0.0f, m_paint.opacity, 1.0f);
		}
	}
}

etk::Pair<etk::Color<float,4>, etk::String> esvg::Base::parseColor(const etk::String& _inputData) {
	etk::Pair<etk::Color<float,4>, etk::String> localColor(etk::color::white, "");
	
	if(    _inputData.size() > 4
	    && _inputData[0] == 'u'
	    && _inputData[1] == 'r'
	    && _inputData[2] == 'l'
	    && _inputData[3] == '(') {
		if (_inputData[4] == '#') {
			etk::String color(_inputData.begin() + 5, _inputData.end()-1);
			localColor = etk::Pair<etk::Color<float,4>, etk::String>(etk::color::none, color);
		} else {
			ESVG_ERROR("Problem in parsing the color : \"" << _inputData << "\"  == > url(XXX) is not supported now ...");
		}
	} else {
		localColor = etk::Pair<etk::Color<float,4>, etk::String>(_inputData, "");
	}
	ESVG_VERBOSE("Parse color : \"" << _inputData << "\"  == > " << localColor.first << " " << localColor.second);
	return localColor;
}

bool esvg::Base::parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax) {
	// TODO : UNDERSTAND why nothing is done here ...
	// Parse basic elements (ID...):
	m_id = _element.attributes["id"];
	_sizeMax = vec2(0.0f, 0.0f);
	return false;
}


const char * esvg::Base::spacingDist(int32_t _spacing) {
	static const char *tmpValue = "                                                                                ";
	if (_spacing>20) {
		_spacing = 20;
	}
	return tmpValue + 20*4 - _spacing*4;
}

void esvg::Base::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) {
	ESVG_WARNING(spacingDist(_level) << "DRAW esvg::Base ... ==> No drawing availlable");
}



const etk::String& esvg::Base::getId() const {
	return m_id;
}

void esvg::Base::setId(const etk::String& _newId) {
	// TODO : Check if it is UNIQUE ...
	m_id = _newId;
}


void esvg::Base::drawShapePoints(etk::Vector<etk::Vector<vec2>>& _out,
                                 int32_t _recurtionMax,
                                 float _threshold,
                                 mat2x3& _basicTrans,
                                 int32_t _level) {
	
}


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <esvg/Debug.h>
#include <esvg/Base.h>
#include <math.h>


#undef __class__
#define __class__	"Base"

esvg::Base::Base(PaintState _parentPaintState) {
	// copy the parent painting properties ...
	m_paint = _parentPaintState;
}

void esvg::Base::parseTransform(exml::Element* _element) {
	if (NULL == _element) {
		return;
	}
	etk::UString inputString = _element->getAttribute("transform");
	if (inputString.size() == 0) {
		return;
	}
	SVG_VERBOSE("find transform : \"" << inputString << "\"");
	for (int32_t iii=0; iii<inputString.size(); iii++) {
		if (inputString[iii] == ',') {
			inputString[iii] = ' ';
		}
	}
	SVG_VERBOSE("find transform : \"" << inputString << "\"");
	double matrix[6];
	float angle, xxx, yyy;
	int32_t n;
	etk::Char myData = inputString.c_str();
	const char * pointerOnData = myData;
	while (*pointerOnData) {
		if (sscanf(pointerOnData, "matrix (%lf %lf %lf %lf %lf %lf) %n", &matrix[0], &matrix[1], &matrix[2], &matrix[3], &matrix[4], &matrix[5], &n) == 6) {
			m_transformMatrix.load_from(matrix);
		} else if (sscanf(pointerOnData, "translate (%f %f) %n", &xxx, &yyy, &n) == 2) {
			m_transformMatrix *= agg::trans_affine_translation(xxx, yyy);
			SVG_VERBOSE("Translate : " << xxx << ", " << yyy);
		} else if (sscanf(pointerOnData, "translate (%f) %n", &xxx, &n) == 1) {
			m_transformMatrix *= agg::trans_affine_translation(xxx, 0);
			SVG_VERBOSE("Translate : " << xxx << ", " << 0);
		} else if (sscanf(pointerOnData, "scale (%f %f) %n", &xxx, &yyy, &n) == 2) {
			m_transformMatrix *= agg::trans_affine_scaling(xxx, yyy);
			SVG_VERBOSE("Scale : " << xxx << ", " << yyy);
		} else if (sscanf(pointerOnData, "scale (%f) %n", &xxx, &n) == 1) {
			m_transformMatrix *= agg::trans_affine_scaling(xxx, xxx);
			SVG_VERBOSE("Scale : " << xxx << ", " << xxx);
		} else if (sscanf(pointerOnData, "rotate (%f %f %f) %n", &angle, &xxx, &yyy, &n) == 3) {
			angle = angle / 180 * M_PI;
			m_transformMatrix *= agg::trans_affine_translation(-xxx, -yyy);
			m_transformMatrix *= agg::trans_affine_rotation(angle);
			m_transformMatrix *= agg::trans_affine_translation(xxx, yyy);
		} else if (sscanf(pointerOnData, "rotate (%f) %n", &angle, &n) == 1) {
			angle = angle / 180 * M_PI;
			SVG_VERBOSE("rotate : " << angle << "rad, " << (angle/M_PI*180) << "°");
			m_transformMatrix *= agg::trans_affine_rotation(angle);
		} else if (sscanf(pointerOnData, "skewX (%f) %n", &angle, &n) == 1) {
			angle = angle / 180 * M_PI;
			SVG_VERBOSE("skewX : " << angle << "rad, " << (angle/M_PI*180) << "°");
			m_transformMatrix *= agg::trans_affine_skewing(angle, 0.0);
		} else if (sscanf(pointerOnData, "skewY (%f) %n", &angle, &n) == 1) {
			angle = angle / 180 * M_PI;
			SVG_VERBOSE("skewY : " << angle << "rad, " << (angle/M_PI*180) << "°");
			m_transformMatrix *= agg::trans_affine_skewing(0.0, angle);
		} else {
			break;
		}
		pointerOnData += n;
	}
}


/**
 * @brief parse x, y, width, height attribute of the xml node
 * @param[in] _element XML node
 * @param[out] _pos parsed position
 * @param[out] _size parsed dimention
 */
void esvg::Base::parsePosition(const exml::Element *_element, etk::Vector2D<float> &_pos, etk::Vector2D<float> &_size) {
	_pos.setValue(0,0);
	_size.setValue(0,0);
	
	if (NULL == _element) {
		return;
	}
	etk::UString content = _element->getAttribute("x");
	if (content.size()!=0) {
		_pos.setX(parseLength(content));
	}
	content = _element->getAttribute("y");
	if (content.size()!=0) {
		_pos.setX(parseLength(content));
	}
	content = _element->getAttribute("width");
	if (content.size()!=0) {
		_size.setX(parseLength(content));
	}
	content = _element->getAttribute("height");
	if (content.size()!=0) {
		_size.setY(parseLength(content));
	}
}


/**
 * @brief parse a lenght of the xml element
 * @param[in] _dataInput Data C String with the printed lenght
 * @return standart number of pixels
 */
float esvg::Base::parseLength(const etk::UString& _dataInput) {
	SVG_VERBOSE(" lenght : '" << _dataInput << "'");
	float n = _dataInput.toFloat();
	etk::UString unit;
	for (int32_t iii=0; iii<_dataInput.size(); iii++) {
		if(    (_dataInput[iii]>='0' && _dataInput[iii]<='9')
		    || _dataInput[iii]<='+'
		    || _dataInput[iii]<='-'
		    || _dataInput[iii]<='.') {
			continue;
		}
		unit = _dataInput.extract(iii-1);
	}
	//SVG_INFO("           == > ?? = " << n );
	float font_size = 20.0f;
	
	SVG_VERBOSE(" lenght : '" << n << "' => unit=" << unit);
	// note : ";" is for the parsing of the style elements ...
	if(    unit.size() == 0
	    || unit[0] == ';' ) {
		return n;
	} else if (unit[0] == '%') {                   // xxx %
		return n / 100.0 * m_paint.viewPort.x();
	} else if (unit[0] == 'e' && unit[1] == 'm') { // xxx em
		return n * font_size;
	} else if (unit[0] == 'e' && unit[1] == 'x') { // xxx ex
		return n / 2.0f * font_size;
	} else if (unit[0] == 'p' && unit[1] == 'x') { // xxx px
		return n;
	} else if (unit[0] == 'p' && unit[1] == 't') { // xxx pt
		return n * 1.25f;
	} else if (unit[0] == 'p' && unit[1] == 'c') { // xxx pc
		return n * 15.0f;
	} else if (unit[0] == 'm' && unit[1] == 'm') { // xxx mm
		return n * 3.543307f;
	} else if (unit[0] == 'c' && unit[1] == 'm') { // xxx cm
		return n * 35.43307f;
	} else if (unit[0] == 'i' && unit[1] == 'n') { // xxx in
		return n * 90.0f;
	}
	return 0.0f;
}

// return the next char position ... (after ';' or NULL)
int32_t extractPartOfStyle(const etk::UString& _data, etk::UString& _outputType, etk::UString& _outputData, int32_t _pos) {
	_outputType = "";
	_outputData = "";
	if (_pos == -1) {
		return -2;
	}
	int32_t typeStart = _pos;
	int32_t typeStop = _pos;
	int32_t dataStart = _pos;
	int32_t dataStop = _pos;
	bool processFirst=true;
	//SVG_DEBUG("parse : '" << _data.Extract(_pos) << "'");
	for( int32_t iii=_pos; iii<_data.size(); iii++) {
		//SVG_DEBUG("   ? '" << _data[iii] << "'");
		if (_data[iii] == ';') {
			// end of the element
			return iii+1;
		}
		if (_data[iii] == ' ') {
			// nothing to do ... we do not copy espaces ...
		} else if (_data[iii] == ':') {
			processFirst = false;
		} else {
			if (processFirst) {
				_outputType += _data[iii];
			} else {
				_outputData += _data[iii];
			}
		}
	}
	SVG_VERBOSE("    extract : '" << _outputType << "':'" << _outputData << "'");
	return -1;
}

/**
 * @brief parse a Painting attribute of a specific node
 * @param[in] _element Basic node of the XML that might be parsed
 */
void esvg::Base::parsePaintAttr(const exml::Element *_element) {
	if (_element == NULL) {
		return;
	}
	bool fillNone = false;
	bool strokeNone = false;
	etk::UString content = _element->getAttribute("fill");
	if (content.size()!=0) {
		m_paint.fill = parseColor(content);
		if (m_paint.fill.a == 0) {
			fillNone = true;
		}
	}
	content = _element->getAttribute("stroke");
	if (content.size()!=0) {
		m_paint.stroke = parseColor(content);
		if (m_paint.stroke.a == 0) {
			strokeNone = true;
		}
	}
	content = _element->getAttribute("stroke-width");
	if (content.size()!=0) {
		m_paint.strokeWidth = parseLength(content);
	}
	content = _element->getAttribute("opacity");
	if (content.size()!=0) {
		float opacity = parseLength(content);
		opacity  = etk_max(0.0, etk_min(1.0, opacity));
		m_paint.fill.a = opacity*0xFF;
		m_paint.stroke.a = opacity*0xFF;
	}
	content = _element->getAttribute("fill-opacity");
	if (content.size()!=0) {
		float opacity = parseLength(content);
		opacity  = etk_max(0.0, etk_min(1.0, opacity));
		m_paint.fill.a = opacity*0xFF;
	}
	content = _element->getAttribute("stroke-opacity");
	if (content.size()!=0) {
		float opacity = parseLength(content);
		opacity  = etk_max(0.0, etk_min(1.0, opacity));
		m_paint.stroke.a = opacity*0xFF;
	}
	content = _element->getAttribute("fill-rule");
	if (content.size()!=0) {
		if (content == "nonzero") {
			m_paint.flagEvenOdd = false;
		} else if (content == "evenodd" ) {
			m_paint.flagEvenOdd = true;
		} else {
			SVG_ERROR("not know fill-rule value : \"" << content << "\", not in [nonzero,evenodd]");
		}
	}
	content = _element->getAttribute("stroke-linecap");
	if (content.size()!=0) {
		if (content == "butt" ) {
			m_paint.lineCap = esvg::lineCapButt;
		} else if (content == "round" ) {
			m_paint.lineCap = esvg::lineCapRound;
		} else if (content == "square" ) {
			m_paint.lineCap = esvg::lineCapSquare;
		} else {
			m_paint.lineCap = esvg::lineCapButt;
			SVG_ERROR("not know stroke-linecap value : \"" << content << "\", not in [butt,round,square]");
		}
	}
	content = _element->getAttribute("stroke-linejoin");
	if (content.size()!=0) {
		if (content == "miter" ) {
			m_paint.lineJoin = esvg::lineJoinMiter;
		} else if (content == "round" ) {
			m_paint.lineJoin = esvg::lineJoinRound;
		} else if (content == "bevel" ) {
			m_paint.lineJoin = esvg::lineJoinBevel;
		} else {
			m_paint.lineJoin = esvg::lineJoinMiter;
			SVG_ERROR("not know stroke-linejoin value : \"" << content << "\", not in [miter,round,bevel]");
		}
	}
	content = _element->getAttribute("style");
	if (content.size()!=0) {
		etk::UString outputType;
		etk::UString outputValue;
		
		for( int32_t sss=extractPartOfStyle(content, outputType, outputValue, 0);
		     -2 != sss;
		     sss=extractPartOfStyle(content, outputType, outputValue, sss) ) {
			SVG_VERBOSE(" style parse : \"" << outputType << "\" with value : \"" << outputValue << "\"");
			if (outputType == "fill") {
				m_paint.fill = parseColor(outputValue);
				SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << m_paint.fill);
				if (m_paint.fill.a == 0) {
					fillNone = true;
				}
			} else if (outputType == "stroke") {
				m_paint.stroke = parseColor(outputValue);
				SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << m_paint.stroke);
				if (m_paint.stroke.a == 0) {
					strokeNone = true;
				}
			} else if (outputType == "stroke-width" ) {
				m_paint.strokeWidth = parseLength(outputValue);
				SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << m_paint.strokeWidth);
			} else if (outputType == "opacity" ) {
				float opacity = parseLength(outputValue);
				opacity  = etk_max(0.0, etk_min(1.0, opacity));
				m_paint.fill.a = opacity*0xFF;
				m_paint.stroke.a = opacity*0xFF;
				SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << m_paint.fill);
			} else if (outputType == "fill-opacity") {
				float opacity = parseLength(outputValue);
				opacity  = etk_max(0.0, etk_min(1.0, opacity));
				m_paint.fill.a = opacity*0xFF;
				SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << m_paint.fill);
			} else if (outputType == "stroke-opacity") {
				float opacity = parseLength(outputValue);
				opacity  = etk_max(0.0, etk_min(1.0, opacity));
				m_paint.stroke.a = opacity*0xFF;
				SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << m_paint.stroke);
			} else if (outputType == "fill-rule" ) {
				if (outputValue == "nonzero" ) {
					m_paint.flagEvenOdd = false;
				} else if (outputValue == "evenodd") {
					m_paint.flagEvenOdd = true;
				} else {
					SVG_ERROR("not know  " << outputType << " value : \"" << outputValue << "\", not in [nonzero,evenodd]");
				}
			} else if (outputType == "stroke-linecap") {
				if (outputValue == "butt") {
					m_paint.lineCap = esvg::lineCapButt;
				} else if (outputValue == "round") {
					m_paint.lineCap = esvg::lineCapRound;
				} else if (outputValue == "square") {
					m_paint.lineCap = esvg::lineCapSquare;
				} else {
					m_paint.lineCap = esvg::lineCapButt;
					SVG_ERROR("not know  " << outputType << " value : \"" << outputValue << "\", not in [butt,round,square]");
				}
			} else if (outputType == "stroke-linejoin") {
				if (outputValue == "miter") {
					m_paint.lineJoin = esvg::lineJoinMiter;
				} else if (outputValue == "round") {
					m_paint.lineJoin = esvg::lineJoinRound;
				} else if (outputValue == "bevel") {
					m_paint.lineJoin = esvg::lineJoinBevel;
				} else {
					m_paint.lineJoin = esvg::lineJoinMiter;
					SVG_ERROR("not know  " << outputType << " value : \"" << outputValue << "\", not in [miter,round,bevel]");
				}
			} else if (outputType == "marker-start") {
				// TODO : ...
			} else {
				SVG_ERROR("not know painting element in style balise : \"" << outputType << "\" with value : \"" << outputValue << "\"");
			}
		}
	}
	// check if somewere none is set to the filling:
	if (true == fillNone) {
		m_paint.fill.a = 0;
	}
	if (true == strokeNone) {
		m_paint.stroke.a = 0;
	}
}

/**
 * @brief parse a color specification from the svg file
 * @param[in] _inputData Data C String with the xml definition
 * @return the parsed color
 */
draw::Color esvg::Base::parseColor(const etk::UString& _inputData) {
	draw::Color localColor = draw::color::white;
	
	if(    _inputData.size() > 4
	    && _inputData[0] == 'u'
	    && _inputData[1] == 'r'
	    && _inputData[2] == 'l'
	    && _inputData[3] == '(') {
		if (_inputData[4] == '#') {
			// TODO : parse gradient ...
		}
		SVG_ERROR(" pb in parsing the color : \"" << _inputData << "\"  == > url(XXX) is not supported now ...");
	} else {
		localColor = _inputData.c_str();
	}
	SVG_VERBOSE("Parse color : \"" << _inputData << "\"  == > " << localColor);
	return localColor;
}


/**
 * @brief parse all the element needed in the basic node
 * @param[in] _element standart XML node
 * @return true if no problem arrived
 */
bool esvg::Base::parse(exml::Element* _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	SVG_ERROR("NOT IMPLEMENTED");
	_sizeMax.setValue(0,0);
	return false;
}


const char * esvg::Base::spacingDist(int32_t _spacing) {
	static const char *tmpValue = "                                                                                ";
	if (_spacing>20) {
		_spacing = 20;
	}
	return tmpValue + 20*4 - _spacing*4;
}


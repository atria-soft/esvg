/**
 *******************************************************************************
 * @file parserSVG/Base.cpp
 * @brief basic Element parsing (Sources)
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
#include <parserSVG/Base.h>
#include <math.h>

svg::Base::Base(PaintState parentPaintState)
{
	// copy the parent painting properties ...
	m_paint = parentPaintState;
}

/**
 * @brief Parse the transform balise C String.
 * @param[in] inputString String data inside the transform attribute
 * @param[in,out] baseMatrice matrice that must be update
 * @return ---
 */
void svg::Base::ParseTransform(TiXmlNode *node)
{
	SVG_CHECK_INOUT(node);
	const char * inputString = (char*)node->ToElement()->Attribute("transform");
	if (NULL == inputString) {
		return;
	}
	SVG_VERBOSE("find transform : \"" << inputString << "\"");
	char tmpData[2048];
	for (int32_t iii=0; inputString[iii]!='\0' && iii<2047; iii++) {
		if (inputString[iii] == ',') {
			tmpData[iii] = ' ';
		} else {
			tmpData[iii] = inputString[iii];
		}
		// end of the string ...
		tmpData[iii+1] = '\0';
	}
	SVG_VERBOSE("find transform : \"" << tmpData << "\"");
	double matrix[6];
	float angle, xxx, yyy;
	int32_t n;
	char * pointerOnData = tmpData;
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
			SVG_VERBOSE("skewX : " << angle << "rad, " << (angle/M_PI*180) << "\Uffffffff");
			m_transformMatrix *= agg::trans_affine_skewing(angle, 0.0);
		} else if (sscanf(pointerOnData, "skewY (%f) %n", &angle, &n) == 1) {
			angle = angle / 180 * M_PI;
			SVG_VERBOSE("skewY : " << angle << "rad, " << (angle/M_PI*180) << "\Uffffffff");
			m_transformMatrix *= agg::trans_affine_skewing(0.0, angle);
		} else {
			break;
		}
		pointerOnData += n;
	}
}


/**
 * @brief Parse x, y, width, height attribute of the xml node
 * @param[in] node XML node
 * @param[out] pos parsed position
 * @param[out] size parsed dimention
 * @return ---
 */
void svg::Base::ParsePosition(const TiXmlNode *node, Vector2D<float> &pos, Vector2D<float> &size)
{
	pos.x = 0;
	pos.y = 0;
	size.x = 0;
	size.y = 0;

	const char * content = node->ToElement()->Attribute("x");
	if (NULL != content) {
		pos.x = ParseLength(content);
	}
	content = node->ToElement()->Attribute("y");
	if (NULL != content) {
		pos.y = ParseLength(content);
	}
	content = node->ToElement()->Attribute("width");
	if (NULL != content) {
		size.x = ParseLength(content);
	}
	content = node->ToElement()->Attribute("height");
	if (NULL != content) {
		size.y = ParseLength(content);
	}
}


/**
 * @brief Parse a lenght of the xml element
 * @param[in] dataInput Data C String with the printed lenght
 * @return standart number of pixels
 */
float svg::Base::ParseLength(const char *dataInput)
{
	int32_t numLength = strspn(dataInput, "0123456789+-.");
	const char *unit = dataInput + numLength;
	//SVG_INFO("          ==> \"" << dataInput << "\"");
	float n = atof(dataInput);
	//SVG_INFO("          ==> ?? = " << n );
	float font_size = 20.0;
	
	// note : ";" is for the parsing of the style elements ...
	if (unit[0] == '\0' || unit[0] == ';' ) {
		return n;
	} else if (unit[0] == '%') {                   // xxx %
		return n / 100.0 * m_paint.viewPort.x;
	} else if (unit[0] == 'e' && unit[1] == 'm') { // xxx em
		return n * font_size;
	} else if (unit[0] == 'e' && unit[1] == 'x') { // xxx ex
		return n / 2.0 * font_size;
	} else if (unit[0] == 'p' && unit[1] == 'x') { // xxx px
		return n;
	} else if (unit[0] == 'p' && unit[1] == 't') { // xxx pt
		return n * 1.25;
	} else if (unit[0] == 'p' && unit[1] == 'c') { // xxx pc
		return n * 15.0;
	} else if (unit[0] == 'm' && unit[1] == 'm') { // xxx mm
		return n * 3.543307;
	} else if (unit[0] == 'c' && unit[1] == 'm') { // xxx cm
		return n * 35.43307;
	} else if (unit[0] == 'i' && unit[1] == 'n') { // xxx in
		return n * 90;
	}
	return 0;
}

// return the next char position ... (after ';' or NULL)
const char * extractPartOfStyle(const char * input, char * outputType, char * outputData, int32_t maxLen)
{
	if (*input == '\0') {
		return NULL;
	}
	int32_t jjj = 0;
	const char * outputPointer = NULL;
	outputType[maxLen-1] = '\0';
	outputType[0] = '\0';
	outputData[maxLen-1] = '\0';
	outputData[0] = '\0';
	char * output = outputType;
	for( int32_t iii=0; iii<maxLen-1 && input[iii]!='\0'; iii++) {
		outputPointer = &input[iii];
		if (input[iii] != ';') {
			if (input[iii] == ' ') {
				// nothing to do ... we do not copy espaces ...
			} else if (input[iii] == ':') {
				// change the output ...
				output = outputData;
				jjj = 0;
			} else {
				output[jjj] = input[iii];
				output[jjj+1] = '\0';
				jjj++;
			}
		} else {
			break;
		}
	}
	outputPointer++;
	return outputPointer;
}

/**
 * @brief Parse a Painting attribute of a specific node
 * @param[in] node : basic node of the XML that might be parsed
 * @return ---
 */
void svg::Base::ParsePaintAttr(const TiXmlNode *node)
{
	bool fillNone = false;
	bool strokeNone = false;
	const char * content = node->ToElement()->Attribute("fill");
	if (NULL != content) {
		m_paint.fill = ParseColor(content);
		if (m_paint.fill.alpha == 0) {
			fillNone = true;
		}
	}
	content = node->ToElement()->Attribute("stroke");
	if (NULL != content) {
		m_paint.stroke = ParseColor(content);
		if (m_paint.stroke.alpha == 0) {
			strokeNone = true;
		}
	}
	content = node->ToElement()->Attribute("stroke-width");
	if (NULL != content) {
		m_paint.strokeWidth = ParseLength(content);
	}
	content = node->ToElement()->Attribute("opacity");
	if (NULL != content) {
		float opacity = ParseLength(content);
		opacity  = etk_max(0.0, etk_min(1.0, opacity));
		m_paint.fill.alpha = opacity*0xFF;
		m_paint.stroke.alpha = opacity*0xFF;
	}
	content = node->ToElement()->Attribute("fill-opacity");
	if (NULL != content) {
		float opacity = ParseLength(content);
		opacity  = etk_max(0.0, etk_min(1.0, opacity));
		m_paint.fill.alpha = opacity*0xFF;
	}
	content = node->ToElement()->Attribute("stroke-opacity");
	if (NULL != content) {
		float opacity = ParseLength(content);
		opacity  = etk_max(0.0, etk_min(1.0, opacity));
		m_paint.stroke.alpha = opacity*0xFF;
	}
	content = node->ToElement()->Attribute("fill-rule");
	if (NULL != content) {
		if (0 == strcmp(content, "nonzero") ) {
			m_paint.flagEvenOdd = false;
		} else if (0 == strcmp(content, "evenodd") ) {
			m_paint.flagEvenOdd = true;
		} else {
			SVG_ERROR("not know fill-rule value : \"" << content << "\", not in [nonzero,evenodd]");
		}
	}
	content = node->ToElement()->Attribute("stroke-linecap");
	if (NULL != content) {
		if (0 == strcmp(content, "butt") ) {
			m_paint.lineCap = svg::LINECAP_BUTT;
		} else if (0 == strcmp(content, "round") ) {
			m_paint.lineCap = svg::LINECAP_ROUND;
		} else if (0 == strcmp(content, "square") ) {
			m_paint.lineCap = svg::LINECAP_SQUARE;
		} else {
			m_paint.lineCap = svg::LINECAP_BUTT;
			SVG_ERROR("not know stroke-linecap value : \"" << content << "\", not in [butt,round,square]");
		}
	}
	content = node->ToElement()->Attribute("stroke-linejoin");
	if (NULL != content) {
		if (0 == strcmp(content, "miter") ) {
			m_paint.lineJoin = svg::LINEJOIN_MITER;
		} else if (0 == strcmp(content, "round") ) {
			m_paint.lineJoin = svg::LINEJOIN_ROUND;
		} else if (0 == strcmp(content, "bevel") ) {
			m_paint.lineJoin = svg::LINEJOIN_BEVEL;
		} else {
			m_paint.lineJoin = svg::LINEJOIN_MITER;
			SVG_ERROR("not know stroke-linejoin value : \"" << content << "\", not in [miter,round,bevel]");
		}
	}
	content = node->ToElement()->Attribute("style");
	if (NULL != content) {
		char outputType[1024] = "";
		char outputValue[1024] = "";
		
		for( const char *sss=extractPartOfStyle(content, outputType, outputValue, 1024);
		     NULL != sss;
		     sss=extractPartOfStyle(sss, outputType, outputValue, 1024) ) {
			SVG_VERBOSE(" style parse : \"" << outputType << "\" with value : \"" << outputValue << "\"");
			if (0 == strcmp(outputType, "fill") ) {
				m_paint.fill = ParseColor(outputValue);
				SVG_VERBOSE(" input : \"" << outputValue << "\" ==> " << m_paint.fill);
				if (m_paint.fill.alpha == 0) {
					fillNone = true;
				}
			} else if (0 == strcmp(outputType, "stroke") ) {
				m_paint.stroke = ParseColor(outputValue);
				SVG_VERBOSE(" input : \"" << outputValue << "\" ==> " << m_paint.stroke);
				if (m_paint.stroke.alpha == 0) {
					strokeNone = true;
				}
			} else if (0 == strcmp(outputType, "stroke-width") ) {
				m_paint.strokeWidth = ParseLength(outputValue);
				SVG_VERBOSE(" input : \"" << outputValue << "\" ==> " << m_paint.strokeWidth);
			} else if (0 == strcmp(outputType, "opacity") ) {
				float opacity = ParseLength(outputValue);
				opacity  = etk_max(0.0, etk_min(1.0, opacity));
				m_paint.fill.alpha = opacity*0xFF;
				m_paint.stroke.alpha = opacity*0xFF;
				SVG_VERBOSE(" input : \"" << outputValue << "\" ==> " << m_paint.fill);
			} else if (0 == strcmp(outputType, "fill-opacity") ) {
				float opacity = ParseLength(outputValue);
				opacity  = etk_max(0.0, etk_min(1.0, opacity));
				m_paint.fill.alpha = opacity*0xFF;
				SVG_VERBOSE(" input : \"" << outputValue << "\" ==> " << m_paint.fill);
			} else if (0 == strcmp(outputType, "stroke-opacity") ) {
				float opacity = ParseLength(outputValue);
				opacity  = etk_max(0.0, etk_min(1.0, opacity));
				m_paint.stroke.alpha = opacity*0xFF;
				SVG_VERBOSE(" input : \"" << outputValue << "\" ==> " << m_paint.stroke);
			} else if (0 == strcmp(outputType, "fill-rule") ) {
				if (0 == strcmp(outputValue, "nonzero") ) {
					m_paint.flagEvenOdd = false;
				} else if (0 == strcmp(outputValue, "evenodd") ) {
					m_paint.flagEvenOdd = true;
				} else {
					SVG_ERROR("not know  " << outputType << " value : \"" << outputValue << "\", not in [nonzero,evenodd]");
				}
			} else if (0 == strcmp(outputType, "stroke-linecap") ) {
				if (0 == strcmp(outputValue, "butt") ) {
					m_paint.lineCap = svg::LINECAP_BUTT;
				} else if (0 == strcmp(outputValue, "round") ) {
					m_paint.lineCap = svg::LINECAP_ROUND;
				} else if (0 == strcmp(outputValue, "square") ) {
					m_paint.lineCap = svg::LINECAP_SQUARE;
				} else {
					m_paint.lineCap = svg::LINECAP_BUTT;
					SVG_ERROR("not know  " << outputType << " value : \"" << outputValue << "\", not in [butt,round,square]");
				}
			} else if (0 == strcmp(outputType, "stroke-linejoin") ) {
				if (0 == strcmp(outputValue, "miter") ) {
					m_paint.lineJoin = svg::LINEJOIN_MITER;
				} else if (0 == strcmp(outputValue, "round") ) {
					m_paint.lineJoin = svg::LINEJOIN_ROUND;
				} else if (0 == strcmp(outputValue, "bevel") ) {
					m_paint.lineJoin = svg::LINEJOIN_BEVEL;
				} else {
					m_paint.lineJoin = svg::LINEJOIN_MITER;
					SVG_ERROR("not know  " << outputType << " value : \"" << outputValue << "\", not in [miter,round,bevel]");
				}
			} else if (0 == strcmp(outputType, "marker-start") ) {
				// TODO : ...
			} else {
				SVG_ERROR("not know painting element in style balise : \"" << outputType << "\" with value : \"" << outputValue << "\"");
			}
		}
	}
	// check if somewere none is set to the filling:
	if (true == fillNone) {
		m_paint.fill.alpha = 0;
	}
	if (true == strokeNone) {
		m_paint.stroke.alpha = 0;
	}
}

bool strnCmpNoCase(const char * input1, const char * input2, int32_t maxLen)
{
	int32_t iii=0;
	while ('\0' != *input1 && '\0' != *input2 && iii < maxLen) {
		char in1 = *input1;
		char in2 = *input2;
		if (in1 != in2) {
			if (in1 <= 'Z' && in1 >= 'A') {
				in1 = in1 - 'A' + 'a';
			}
			if (in2 <= 'Z' && in2 >= 'A') {
				in2 = in2 - 'A' + 'a';
			}
			if (in1 != in2) {
				return false;
			}
		}
		iii++;
		input1++;
		input2++;
	}
	return true;
}


/**
 * @brief Parse a color specification from the svg file
 * @param[in] inputData Data C String with the xml definition
 * @return the parsed color
 */
color_ts svg::Base::ParseColor(const char *inputData)
{
	color_ts localColor = etk::color::color_White;;
	
	size_t len = strlen(inputData);
	
	if(    4 < len
	    && inputData[0] == 'u'
	    && inputData[1] == 'r'
	    && inputData[2] == 'l'
	    && inputData[3] == '(') {
		if (inputData[4] == '#') {
			// TODO : parse gradient ...
		}
		SVG_ERROR(" pb in parsing the color : \"" << inputData << "\" ==> url(XXX) is not supported now ...");
	} else {
		localColor = etk::color::Parse(inputData);
	}
	SVG_VERBOSE("Parse color : \"" << inputData << "\" ==> " << localColor);
	return localColor;
}


/**
 * @brief Parse all the element needed in the basic node
 * @param[in] node standart XML node
 * @return true if no problem arrived
 */
bool svg::Base::Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax)
{
	SVG_ERROR("NOT IMPLEMENTED");
	sizeMax.x = 0;
	sizeMax.y = 0;
	return false;
}


const char * svg::Base::SpacingDist(int32_t spacing)
{
	static const char *tmpValue = "                                                                                ";
	if (spacing>20) {
		spacing = 20;
	}
	return tmpValue + 20*4 - spacing*4;
}


/*
void svg::Base::AggCheckChange(agg::path_storage& path, etk::VectorType<agg::rgba8> &colors, etk::VectorType<uint32_t> &pathIdx, PaintState &curentPaintProp)
{
	if (curentPaintProp != m_paint) {
		SVG_INFO("add path color = " << m_paint.fill);
		// New color. Every new color creates new path in the path object.
		colors.PushBack(agg::rgba8(m_paint.fill.red, m_paint.fill.green, m_paint.fill.blue, m_paint.fill.alpha));
		uint32_t tmpPathNew = path.start_new_path();
		pathIdx.PushBack(tmpPathNew);
		curentPaintProp = m_paint;
	}
}
*/

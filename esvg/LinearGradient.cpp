/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/LinearGradient.h>
#include <esvg/render/Path.h>
#include <esvg/render/Weight.h>

#undef __class__
#define __class__	"LinearGradient"

esvg::LinearGradient::LinearGradient(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	m_pos1.setValue(0,0);
	m_pos2.setValue(0,0);
}

esvg::LinearGradient::~LinearGradient() {
	
}

bool esvg::LinearGradient::parseXML(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	// line must have a minimum size...
	//m_paint.strokeWidth = 1;
	if (_element == nullptr) {
		return false;
	}
	
	// ---------------- get unique ID ----------------
	m_id = _element->getAttribute("id");
	
	//parseTransform(_element);
	//parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	std::string content = _element->getAttribute("x1");
	if (content.size()!=0) {
		m_pos1.setX(parseLength(content));
	}
	content = _element->getAttribute("y1");
	if (content.size()!=0) {
		m_pos1.setY(parseLength(content));
	}
	content = _element->getAttribute("x2");
	if (content.size()!=0) {
		m_pos2.setX(parseLength(content));
	}
	content = _element->getAttribute("y2");
	if (content.size()!=0) {
		m_pos2.setY(parseLength(content));
	}
	
	// parse all sub node :
	for(int32_t iii=0; iii<_element->size() ; iii++) {
		std::shared_ptr<exml::Element> child = _element->getElement(iii);
		if (child == nullptr) {
			// can be a comment ...
			continue;
		}
		if (child->getValue() == "stop") {
			float offset = 0;
			etk::Color<float,4> stopColor = etk::color::none;
			// ---------------- offset ----------------
			content = child->getAttribute("offset");
			if (content.size()!=0) {
				offset = parseLength(content);
				offset = std::avg(0.0f, offset, 100.0f);
			}
			// ---------------- STYLE ----------------
			content = _element->getAttribute("style");
			if (content.size()!=0) {
				std::string outputType;
				std::string outputValue;
				for( int32_t sss=extractPartOfStyle(content, outputType, outputValue, 0);
				     -2 != sss;
				     sss=extractPartOfStyle(content, outputType, outputValue, sss) ) {
					SVG_VERBOSE(" style parse : \"" << outputType << "\" with value : \"" << outputValue << "\"");
					if (outputType == "stop-color") {
						stopColor = parseColor(outputValue);
						SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << stopColor);
					} else if (outputType == "stop-opacity") {
						float opacity = parseLength(outputValue);
						opacity = std::avg(0.0f, opacity, 1.0f);
						stopColor.setA(opacity);
						SVG_VERBOSE(" input : \"" << outputValue << "\"  == > " << stopColor);
					} else {
						SVG_ERROR("not know painting element in style balise : \"" << outputType << "\" with value : \"" << outputValue << "\"");
					}
				}
			}
			m_data.push_back(std::pair<float, etk::Color<float,4>>(offset, stopColor));
		} else {
			SVG_ERROR("(l " << child->getPos() << ") node not suported : \"" << child->getValue() << "\" must be [stop]");
		}
	}
	return true;
}

void esvg::LinearGradient::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "LinearGradient " << m_pos1 << " to " << m_pos2);
	for (auto &it : m_data) {
		SVG_DEBUG(spacingDist(_spacing+1) << "STOP: offset=" << it.first << " color=" << it.second);
	}
}

void esvg::LinearGradient::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::LinearGradient");
}



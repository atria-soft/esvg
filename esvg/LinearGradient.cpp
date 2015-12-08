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
	m_pos1.set(vec2(0,0), esvg::distance_pixel);
	m_pos2.set(vec2(0,0), esvg::distance_pixel);
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
	
	std::string contentX = _element->getAttribute("x1");
	std::string contentY = _element->getAttribute("y1");
	m_pos1.set(contentX, contentY);
	contentX = _element->getAttribute("x2");
	contentY = _element->getAttribute("y2");
	m_pos2.set(contentX, contentY);
	
	// parse all sub node :
	for(int32_t iii=0; iii<_element->size() ; iii++) {
		std::shared_ptr<exml::Element> child = _element->getElement(iii);
		if (child == nullptr) {
			// can be a comment ...
			continue;
		}
		if (child->getValue() == "stop") {
			float offset = 100;
			etk::Color<float,4> stopColor = etk::color::none;
			std::string content = child->getAttribute("offset");
			if (content.size()!=0) {
				std::pair<float, enum esvg::distance> tmp = parseLength2(content);
				if (tmp.second != esvg::distance_pourcent) {
					SVG_ERROR("offset : " << content << " res=" << tmp.first << "," << tmp.second << " Not support other than pourcent %");
				} else {
					offset = tmp.first;
				}
			}
			content = child->getAttribute("stop-color");
			if (content.size()!=0) {
				stopColor = parseColor(content).first;
				SVG_VERBOSE(" color : \"" << content << "\"  == > " << stopColor);
			}
			content = child->getAttribute("stop-opacity");
			if (content.size()!=0) {
				float opacity = parseLength(content);
				opacity = std::avg(0.0f, opacity, 1.0f);
				stopColor.setA(opacity);
				SVG_VERBOSE(" opacity : \"" << content << "\"  == > " << stopColor);
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



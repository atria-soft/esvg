/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/LinearGradient.hpp>
#include <esvg/RadialGradient.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>
#include <esvg/esvg.hpp>

esvg::LinearGradient::LinearGradient(PaintState _parentPaintState) :
  esvg::Base(_parentPaintState),
  m_pos1(vec2(50,50), esvg::distance_pourcent),
  m_pos2(vec2(50,50), esvg::distance_pourcent),
  m_unit(gradientUnits_objectBoundingBox),
  m_spread(spreadMethod_pad) {
	
}

esvg::LinearGradient::~LinearGradient() {
	
}


bool esvg::LinearGradient::parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax) {
	// line must have a minimum size...
	//m_paint.strokeWidth = 1;
	if (_element.exist() == false) {
		return false;
	}
	
	// ---------------- get unique ID ----------------
	m_id = _element.attributes["id"];
	
	//parseTransform(_element);
	//parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	etk::String contentX = _element.attributes["x1"];
	etk::String contentY = _element.attributes["y1"];
	if (    contentX != ""
	     && contentY != "") {
		m_pos1.set(contentX, contentY);
	}
	contentX = _element.attributes["x2"];
	contentY = _element.attributes["y2"];
	if (    contentX != ""
	     && contentY != "") {
		m_pos2.set(contentX, contentY);
	}
	contentX = _element.attributes["gradientUnits"];
	if (contentX == "userSpaceOnUse") {
		m_unit = gradientUnits_userSpaceOnUse;
	} else {
		m_unit = gradientUnits_objectBoundingBox;
		if (    contentX.size() != 0
		     && contentX != "objectBoundingBox") {
			ESVG_ERROR("Parsing error of 'gradientUnits' ==> not suported value: '" << contentX << "' not in : {userSpaceOnUse/objectBoundingBox} use objectBoundingBox");
		}
	}
	contentX = _element.attributes["spreadMethod"];
	if (contentX == "reflect") {
		m_spread = spreadMethod_reflect;
	} else if (contentX == "repeat") {
		m_spread = spreadMethod_repeat;
	} else {
		m_spread = spreadMethod_pad;
		if (    contentX.size() != 0
		     && contentX != "pad") {
			ESVG_ERROR("Parsing error of 'spreadMethod' ==> not suported value: '" << contentX << "' not in : {reflect/repeate/pad} use pad");
		}
	}
	// note: xlink:href is incompatible with subNode "stop"
	m_href = _element.attributes["xlink:href"];
	if (m_href.size() != 0) {
		m_href = etk::String(m_href.begin()+1, m_href.end());
	}
	// parse all sub node :
	for(const auto it : _element.nodes) {
		exml::Element child = it.toElement();
		if (child.exist() == false) {
			// can be a comment ...
			continue;
		}
		if (child.getValue() == "stop") {
			float offset = 100;
			etk::Color<float,4> stopColor = etk::color::none;
			etk::String content = child.attributes["offset"];
			if (content.size()!=0) {
				etk::Pair<float, enum esvg::distance> tmp = parseLength2(content);
				if (tmp.second == esvg::distance_pixel) {
					// special case ==> all time % then no type define ==> % in [0.0 .. 1.0]
					offset = tmp.first*100.0f;
				} else if (tmp.second != esvg::distance_pourcent) {
					ESVG_ERROR("offset : " << content << " res=" << tmp.first << "," << tmp.second << " Not support other than pourcent %");
				} else {
					offset = tmp.first;
				}
			}
			content = child.attributes["stop-color"];
			if (content.size()!=0) {
				stopColor = parseColor(content).first;
				ESVG_VERBOSE(" color : '" << content << "' == > " << stopColor);
			}
			content = child.attributes["stop-opacity"];
			if (content.size()!=0) {
				float opacity = parseLength(content);
				opacity = etk::avg(0.0f, opacity, 1.0f);
				stopColor.setA(opacity);
				ESVG_VERBOSE(" opacity : '" << content << "'  == > " << stopColor);
			}
			m_data.pushBack(etk::Pair<float, etk::Color<float,4>>(offset, stopColor));
		} else {
			ESVG_ERROR("(l " << child.getPos() << ") node not suported : '" << child.getValue() << "' must be [stop]");
		}
	}
	if (m_data.size() != 0) {
		if (m_href != "") {
			ESVG_ERROR("(l " << _element.getPos() << ") node can not have an xlink:href element with sub node named: stop ==> removing href");
			m_href = "";
		}
	}
	return true;
}

void esvg::LinearGradient::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "LinearGradient " << m_pos1 << " to " << m_pos2);
	for (auto &it : m_data) {
		ESVG_DEBUG(spacingDist(_spacing+1) << "STOP: offset=" << it.first << " color=" << it.second);
	}
}

void esvg::LinearGradient::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::LinearGradient");
}

const esvg::Dimension& esvg::LinearGradient::getPosition1() {
	return m_pos1;
}

const esvg::Dimension& esvg::LinearGradient::getPosition2() {
	return m_pos2;
}

const etk::Vector<etk::Pair<float, etk::Color<float,4>>>& esvg::LinearGradient::getColors(esvg::Document* _document) {
	if (m_href == "") {
		return m_data;
	}
	if (_document == null) {
		ESVG_ERROR("Get null input for document");
		return m_data;
	}
	ememory::SharedPtr<esvg::Base> base = _document->getReference(m_href);
	if (base == null) {
		ESVG_ERROR("Can not get base : '" << m_href << "'");
		return m_data;
	}
	ememory::SharedPtr<esvg::RadialGradient> gradientR = ememory::dynamicPointerCast<esvg::RadialGradient>(base);
	if (gradientR == null) {
		ememory::SharedPtr<esvg::LinearGradient> gradientL = ememory::dynamicPointerCast<esvg::LinearGradient>(base);
		if (gradientL == null) {
			ESVG_ERROR("Can not cast in a linear/radial gradient: '" << m_href << "' ==> wrong type");
			return m_data;
		}
		return gradientL->getColors(_document);
	}
	return gradientR->getColors(_document);
}




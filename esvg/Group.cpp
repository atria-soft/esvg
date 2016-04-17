/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Group.h>
#include <etk/types.h>
#include <esvg/Base.h>
#include <esvg/Circle.h>
#include <esvg/Ellipse.h>
#include <esvg/Line.h>
#include <esvg/Path.h>
#include <esvg/Polygon.h>
#include <esvg/Polyline.h>
#include <esvg/Rectangle.h>
#include <esvg/Text.h>
#include <esvg/Group.h>

esvg::Group::Group(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Group::~Group() {
	
}

bool esvg::Group::parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	// parse ...
	vec2 pos(0,0);
	vec2 size(0,0);
	parseTransform(_element);
	parsePosition(_element, pos, size);
	parsePaintAttr(_element);
	ESVG_VERBOSE("parsed G1.   trans : " << m_transformMatrix);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	ESVG_VERBOSE("parsed G2.   trans : " << m_transformMatrix);
	
	_sizeMax.setValue(0,0);
	vec2 tmpPos(0,0);
	// parse all sub node :
	for(const auto it : _element.nodes) {
		exml::Element child = _element.toElement();
		if (child.exist() == false) {
			// can be a comment ...
			continue;
		}
		std::shared_ptr<esvg::Base> elementParser;
		if (child.getValue() == "g") {
			elementParser = std::make_shared<esvg::Group>(m_paint);
		} else if (child.getValue() == "a") {
			// TODO ...
		} else if (child.getValue() == "path") {
			elementParser = std::make_shared<esvg::Path>(m_paint);
		} else if (child.getValue() == "rect") {
			elementParser = std::make_shared<esvg::Rectangle>(m_paint);
		} else if (child.getValue() == "circle") {
			elementParser = std::make_shared<esvg::Circle>(m_paint);
		} else if (child.getValue() == "ellipse") {
			elementParser = std::make_shared<esvg::Ellipse>(m_paint);
		} else if (child.getValue() == "line") {
			elementParser = std::make_shared<esvg::Line>(m_paint);
		} else if (child.getValue() == "polyline") {
			elementParser = std::make_shared<esvg::Polyline>(m_paint);
		} else if (child.getValue() == "polygon") {
			elementParser = std::make_shared<esvg::Polygon>(m_paint);
		} else if (child.getValue() == "text") {
			elementParser = std::make_shared<esvg::Text>(m_paint);
		} else {
			ESVG_ERROR("(l " << child.getPos() << ") node not suported : '" << child.getValue() << "' must be [g,a,path,rect,circle,ellipse,line,polyline,polygon,text]");
		}
		if (elementParser == nullptr) {
			ESVG_ERROR("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' allocation error or not supported ...");
			continue;
		}
		if (elementParser->parseXML(child, m_transformMatrix, tmpPos) == false) {
			ESVG_ERROR("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' Sub Parsing ERROR");
			elementParser.reset();
			continue;
		}
		_sizeMax.setValue(std::max(_sizeMax.x(), tmpPos.x()),
		                  std::max(_sizeMax.y(), tmpPos.y()));
		// add element in the system
		m_subElementList.push_back(elementParser);
	}
	return true;
}

void esvg::Group::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Group (START) fill=" << m_paint.fill.first << "/" << m_paint.fill.second
	                                << " stroke=" << m_paint.stroke.first << "/" << m_paint.stroke.second
	                                << " stroke-width=" << m_paint.strokeWidth );
	for (size_t iii=0; iii<m_subElementList.size(); ++iii) {
		if (m_subElementList[iii] != nullptr) {
			m_subElementList[iii]->display(_spacing+1);
		}
	}
	ESVG_DEBUG(spacingDist(_spacing) << "Group (STOP)");
}

void esvg::Group::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::group");
	for (size_t iii=0; iii<m_subElementList.size(); ++iii) {
		if (m_subElementList[iii] != nullptr) {
			m_subElementList[iii]->draw(_myRenderer, _basicTrans, _level+1);
		}
	}
}


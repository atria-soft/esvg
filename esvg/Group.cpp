/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Group.hpp>
#include <etk/types.hpp>
#include <esvg/Base.hpp>
#include <esvg/Circle.hpp>
#include <esvg/Ellipse.hpp>
#include <esvg/Line.hpp>
#include <esvg/Path.hpp>
#include <esvg/Polygon.hpp>
#include <esvg/Polyline.hpp>
#include <esvg/Rectangle.hpp>
#include <esvg/Text.hpp>
#include <esvg/Group.hpp>

esvg::Group::Group(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Group::~Group() {
	
}

bool esvg::Group::parseXML(const exml::Element& _element, mat2x3& _parentTrans, vec2& _sizeMax) {
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
		exml::Element child = it.toElement();
		if (child.exist() == false) {
			// can be a comment ...
			continue;
		}
		ememory::SharedPtr<esvg::Base> elementParser;
		if (child.getValue() == "g") {
			elementParser = ememory::makeShared<esvg::Group>(m_paint);
		} else if (child.getValue() == "a") {
			// TODO ...
		} else if (child.getValue() == "path") {
			elementParser = ememory::makeShared<esvg::Path>(m_paint);
		} else if (child.getValue() == "rect") {
			elementParser = ememory::makeShared<esvg::Rectangle>(m_paint);
		} else if (child.getValue() == "circle") {
			elementParser = ememory::makeShared<esvg::Circle>(m_paint);
		} else if (child.getValue() == "ellipse") {
			elementParser = ememory::makeShared<esvg::Ellipse>(m_paint);
		} else if (child.getValue() == "line") {
			elementParser = ememory::makeShared<esvg::Line>(m_paint);
		} else if (child.getValue() == "polyline") {
			elementParser = ememory::makeShared<esvg::Polyline>(m_paint);
		} else if (child.getValue() == "polygon") {
			elementParser = ememory::makeShared<esvg::Polygon>(m_paint);
		} else if (child.getValue() == "text") {
			elementParser = ememory::makeShared<esvg::Text>(m_paint);
		} else {
			ESVG_ERROR("(l " << child.getPos() << ") node not suported : '" << child.getValue() << "' must be [g,a,path,rect,circle,ellipse,line,polyline,polygon,text]");
		}
		if (elementParser == null) {
			ESVG_ERROR("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' allocation error or not supported ...");
			continue;
		}
		if (elementParser->parseXML(child, m_transformMatrix, tmpPos) == false) {
			ESVG_ERROR("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' Sub Parsing ERROR");
			elementParser.reset();
			continue;
		}
		_sizeMax.setValue(etk::max(_sizeMax.x(), tmpPos.x()),
		                  etk::max(_sizeMax.y(), tmpPos.y()));
		// add element in the system
		m_subElementList.pushBack(elementParser);
	}
	return true;
}

void esvg::Group::display(int32_t _spacing) {
	ESVG_DEBUG(spacingDist(_spacing) << "Group (START) fill=" << m_paint.fill.first << "/" << m_paint.fill.second
	                                << " stroke=" << m_paint.stroke.first << "/" << m_paint.stroke.second
	                                << " stroke-width=" << m_paint.strokeWidth );
	for (auto &it : m_subElementList) {
		if (it != null) {
			it->display(_spacing+1);
		}
	}
	ESVG_DEBUG(spacingDist(_spacing) << "Group (STOP)");
}

void esvg::Group::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW esvg::group");
	for (auto &it : m_subElementList) {
		if (it != null) {
			it->draw(_myRenderer, _basicTrans, _level+1);
		}
	}
}

void esvg::Group::drawShapePoints(etk::Vector<etk::Vector<vec2>>& _out,
                                  int32_t _recurtionMax,
                                  float _threshold,
                                  mat2x3& _basicTrans,
                                  int32_t _level) {
	ESVG_VERBOSE(spacingDist(_level) << "DRAW shape esvg::group");
	for (auto &it : m_subElementList) {
		if (it != null) {
			it->drawShapePoints(_out, _recurtionMax, _threshold, _basicTrans, _level+1);
		}
	}
}


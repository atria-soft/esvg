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

boolean esvg::Group::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	if (_element.exist() == false) {
		return false;
	}
	// parse ...
	Vector2f pos(0,0);
	Vector2f size(0,0);
	parseTransform(_element);
	parsePosition(_element, pos, size);
	parsePaintAttr(_element);
	Log.verbose("parsed G1.   trans : " << this.transformMatrix);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	Log.verbose("parsed G2.   trans : " << this.transformMatrix);
	
	_sizeMax.setValue(0,0);
	Vector2f tmpPos(0,0);
	// parse all sub node :
	for(const auto it : _element.nodes) {
		exml::Element child = it.toElement();
		if (child.exist() == false) {
			// can be a comment ...
			continue;
		}
		ememory::SharedPtr<esvg::Base> elementParser;
		if (child.getValue() == "g") {
			elementParser = ememory::makeShared<esvg::Group>(this.paint);
		} else if (child.getValue() == "a") {
			// TODO ...
		} else if (child.getValue() == "path") {
			elementParser = ememory::makeShared<esvg::Path>(this.paint);
		} else if (child.getValue() == "rect") {
			elementParser = ememory::makeShared<esvg::Rectangle>(this.paint);
		} else if (child.getValue() == "circle") {
			elementParser = ememory::makeShared<esvg::Circle>(this.paint);
		} else if (child.getValue() == "ellipse") {
			elementParser = ememory::makeShared<esvg::Ellipse>(this.paint);
		} else if (child.getValue() == "line") {
			elementParser = ememory::makeShared<esvg::Line>(this.paint);
		} else if (child.getValue() == "polyline") {
			elementParser = ememory::makeShared<esvg::Polyline>(this.paint);
		} else if (child.getValue() == "polygon") {
			elementParser = ememory::makeShared<esvg::Polygon>(this.paint);
		} else if (child.getValue() == "text") {
			elementParser = ememory::makeShared<esvg::Text>(this.paint);
		} else {
			Log.error("(l " << child.getPos() << ") node not suported : '" << child.getValue() << "' must be [g,a,path,rect,circle,ellipse,line,polyline,polygon,text]");
		}
		if (elementParser == null) {
			Log.error("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' allocation error or not supported ...");
			continue;
		}
		if (elementParser->parseXML(child, this.transformMatrix, tmpPos) == false) {
			Log.error("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' Sub Parsing ERROR");
			elementParser.reset();
			continue;
		}
		_sizeMax.setValue(etk::max(_sizeMax.x(), tmpPos.x()),
		                  etk::max(_sizeMax.y(), tmpPos.y()));
		// add element in the system
		this.subElementList.pushBack(elementParser);
	}
	return true;
}

void esvg::Group::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "Group (START) fill=" << this.paint.fill.first << "/" << this.paint.fill.second
	                                << " stroke=" << this.paint.stroke.first << "/" << this.paint.stroke.second
	                                << " stroke-width=" << this.paint.strokeWidth );
	for (auto &it : this.subElementList) {
		if (it != null) {
			it->display(_spacing+1);
		}
	}
	Log.debug(spacingDist(_spacing) << "Group (STOP)");
}

void esvg::Group::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::group");
	for (auto &it : this.subElementList) {
		if (it != null) {
			it->draw(_myRenderer, _basicTrans, _level+1);
		}
	}
}

void esvg::Group::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                  int _recurtionMax,
                                  float _threshold,
                                  mat2x3& _basicTrans,
                                  int _level) {
	Log.verbose(spacingDist(_level) << "DRAW shape esvg::group");
	for (auto &it : this.subElementList) {
		if (it != null) {
			it->drawShapePoints(_out, _recurtionMax, _threshold, _basicTrans, _level+1);
		}
	}
}


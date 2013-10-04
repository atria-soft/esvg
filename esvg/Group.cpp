/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/Debug.h>
#include <esvg/Group.h>
#include <etk/UString.h>
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

#undef __class__
#define __class__	"Group"

esvg::Group::Group(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Group::~Group(void) {
	
}

bool esvg::Group::parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax) {
	if (NULL == _element) {
		return false;
	}
	// parse ...
	etk::Vector2D<float> pos(0,0);
	etk::Vector2D<float> size(0,0);
	parseTransform(_element);
	parsePosition(_element, pos, size);
	parsePaintAttr(_element);
	SVG_VERBOSE("parsed G1.   trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	SVG_VERBOSE("parsed G2.   trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	
	_sizeMax.setValue(0,0);
	vec2 tmpPos(0,0);
	// parse all sub node :
	for(int32_t iii=0; iii<_element->size() ; iii++) {
		exml::Element* child = _element->getElement(iii);
		if (NULL == child) {
			// can be a comment ...
			continue;
		}
		esvg::Base *elementParser = NULL;
		if (child->getValue() == "g") {
			elementParser = new esvg::Group(m_paint);
		} else if (child->getValue() == "a") {
			// TODO ...
		} else if (child->getValue() == "path") {
			elementParser = new esvg::Path(m_paint);
		} else if (child->getValue() == "rect") {
			elementParser = new esvg::Rectangle(m_paint);
		} else if (child->getValue() == "circle") {
			elementParser = new esvg::Circle(m_paint);
		} else if (child->getValue() == "ellipse") {
			elementParser = new esvg::Ellipse(m_paint);
		} else if (child->getValue() == "line") {
			elementParser = new esvg::Line(m_paint);
		} else if (child->getValue() == "polyline") {
			elementParser = new esvg::Polyline(m_paint);
		} else if (child->getValue() == "polygon") {
			elementParser = new esvg::Polygon(m_paint);
		} else if (child->getValue() == "text") {
			elementParser = new esvg::Text(m_paint);
		} else {
			SVG_ERROR("(l "<<child->getPos()<<") node not suported : \""<<child->getValue()<<"\" must be [g,a,path,rect,circle,ellipse,line,polyline,polygon,text]");
		}
		if (NULL == elementParser) {
			SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" allocation error or not supported ...");
		} else {
			if (false == elementParser->parse(child, m_transformMatrix, tmpPos)) {
				SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" Sub Parsing ERROR");
				delete(elementParser);
				elementParser = NULL;
			} else {
				_sizeMax.setValue(etk_max(_sizeMax.x(), tmpPos.x()),
				                  etk_max(_sizeMax.y(), tmpPos.y()));
				// add element in the system
				m_subElementList.pushBack(elementParser);
			}
		}
	}
	return true;
}

void esvg::Group::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Group (START) fill=" << m_paint.fill << " stroke=" << m_paint.stroke << " stroke-width=" << m_paint.strokeWidth );
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->display(_spacing+1);
		}
	}
	SVG_DEBUG(spacingDist(_spacing) << "Group (STOP)");
}

void esvg::Group::aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->aggDraw(_myRenderer, _basicTrans);
		}
	}
}


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Group.h>
#include <etk/UString.h>
#include <parserSVG/Base.h>
#include <parserSVG/Circle.h>
#include <parserSVG/Ellipse.h>
#include <parserSVG/Line.h>
#include <parserSVG/Path.h>
#include <parserSVG/Polygon.h>
#include <parserSVG/Polyline.h>
#include <parserSVG/Rectangle.h>
#include <parserSVG/Text.h>
#include <parserSVG/Group.h>

svg::Group::Group(PaintState _parentPaintState) : svg::Base(_parentPaintState)
{
	
}

svg::Group::~Group(void)
{
	
}

bool svg::Group::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	if (NULL==_element) {
		return false;
	}
	// parse ...
	etk::Vector2D<float> pos(0,0);
	etk::Vector2D<float> size(0,0);
	ParseTransform(_element);
	ParsePosition(_element, pos, size);
	ParsePaintAttr(_element);
	SVG_VERBOSE("parsed G1.   trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	SVG_VERBOSE("parsed G2.   trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	
	_sizeMax.setValue(0,0);
	vec2 tmpPos(0,0);
	// parse all sub node :
	for(int32_t iii=0; iii<_element->Size() ; iii++) {
		exml::Node* child = _element->Get(iii);
		if (NULL == child) {
			continue;
		}
		if (!child->IsElement()) {
			// nothing to do, just proceed to next step
			continue;
		}
		svg::Base *elementParser = NULL;
		if (child->GetValue() == "g") {
			elementParser = new svg::Group(m_paint);
		} else if (child->GetValue() == "a") {
			// TODO ...
		} else if (child->GetValue() == "path") {
			elementParser = new svg::Path(m_paint);
		} else if (child->GetValue() == "rect") {
			elementParser = new svg::Rectangle(m_paint);
		} else if (child->GetValue() == "circle") {
			elementParser = new svg::Circle(m_paint);
		} else if (child->GetValue() == "ellipse") {
			elementParser = new svg::Ellipse(m_paint);
		} else if (child->GetValue() == "line") {
			elementParser = new svg::Line(m_paint);
		} else if (child->GetValue() == "polyline") {
			elementParser = new svg::Polyline(m_paint);
		} else if (child->GetValue() == "polygon") {
			elementParser = new svg::Polygon(m_paint);
		} else if (child->GetValue() == "text") {
			elementParser = new svg::Text(m_paint);
		} else {
			SVG_ERROR("(l "<<child->Pos()<<") node not suported : \""<<child->GetValue()<<"\" must be [g,a,path,rect,circle,ellipse,line,polyline,polygon,text]");
		}
		if (NULL == elementParser) {
			SVG_ERROR("(l "<<child->Pos()<<") error on node: \""<<child->GetValue()<<"\" allocation error or not supported ...");
		} else {
			if (false == elementParser->Parse((exml::Element*)child, m_transformMatrix, tmpPos)) {
				SVG_ERROR("(l "<<child->Pos()<<") error on node: \""<<child->GetValue()<<"\" Sub Parsing ERROR");
				delete(elementParser);
				elementParser = NULL;
			} else {
				_sizeMax.setValue(etk_max(_sizeMax.x(), tmpPos.x()),
				                  etk_max(_sizeMax.y(), tmpPos.y()));
				// add element in the system
				m_subElementList.PushBack(elementParser);
			}
		}
	}
	return true;
}

void svg::Group::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Group (START) fill=" << m_paint.fill << " stroke=" << m_paint.stroke << " stroke-width=" << m_paint.strokeWidth );
	for (int32_t iii=0; iii<m_subElementList.Size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->Display(_spacing+1);
		}
	}
	SVG_DEBUG(SpacingDist(_spacing) << "Group (STOP)");
}

void svg::Group::AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	for (int32_t iii=0; iii<m_subElementList.Size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->AggDraw(_myRenderer, _basicTrans);
		}
	}
}


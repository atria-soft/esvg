/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <parserSVG/Debug.h>
#include <parserSVG/Polyline.h>
#include <agg/agg_conv_stroke.h>
#include <agg/agg_path_storage.h>

svg::Polyline::Polyline(PaintState _parentPaintState) : svg::Base(_parentPaintState)
{
	
}

svg::Polyline::~Polyline(void)
{
	
}

bool svg::Polyline::Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax)
{
	// line must have a minimum size...
	m_paint.strokeWidth = 1;
	if (NULL==_element) {
		return false;
	}
	ParseTransform(_element);
	ParsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	etk::UString sss1 = _element->GetAttribute("points");
	if (sss1.Size()==0) {
		SVG_ERROR("(l "<<_element->Pos()<<") polyline: missing points attribute");
		return false;
	}
	_sizeMax.setValue(0,0);
	SVG_VERBOSE("Parse polyline : \"" << sss1 << "\"");
	etk::Char sss2 = sss1.c_str();
	const char* sss = sss2;
	while ('\0' != sss[0]) {
		etk::Vector2D<float> pos;
		int32_t n;
		if (sscanf(sss, "%f,%f %n", &pos.m_floats[0], &pos.m_floats[1], &n) == 2) {
			m_listPoint.PushBack(pos);
			_sizeMax.setValue(etk_max(_sizeMax.x(), pos.x()),
			                  etk_max(_sizeMax.y(), pos.y()));
			sss += n;
		} else {
			break;
		}
	}
	return true;
}

void svg::Polyline::Display(int32_t _spacing)
{
	SVG_DEBUG(SpacingDist(_spacing) << "Polyline nbPoint=" << m_listPoint.Size());
}


void svg::Polyline::AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	agg::path_storage path;
	path.start_new_path();
	path.move_to(m_listPoint[0].x(), m_listPoint[0].y());
	for( int32_t iii=1; iii< m_listPoint.Size(); iii++) {
		path.line_to(m_listPoint[iii].x(), m_listPoint[iii].y());
	}
	/*
	// configure the end of the line : 
	switch (m_paint.lineCap) {
		case svg::LINECAP_SQUARE:
			path.line_cap(agg::square_cap);
			break;
		case svg::LINECAP_ROUND:
			path.line_cap(agg::round_cap);
			break;
		default: // svg::LINECAP_BUTT
			path.line_cap(agg::butt_cap);
			break;
	}
	switch (m_paint.lineJoin) {
		case svg::LINEJOIN_BEVEL:
			path.line_join(agg::bevel_join);
			break;
		case svg::LINEJOIN_ROUND:
			path.line_join(agg::round_join);
			break;
		default: // svg::LINEJOIN_MITER
			path.line_join(agg::miter_join);
			break;
	}
	*/
	
	agg::trans_affine mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	if (m_paint.strokeWidth > 0) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// Drawing as an outline
		agg::conv_stroke<agg::path_storage> myPolygonStroke(path);
		myPolygonStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::path_storage>, agg::trans_affine> transStroke(myPolygonStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
}



/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Ellipse.h>

#undef __class__
#define __class__	"Ellipse"

esvg::Ellipse::Ellipse(PaintState _parentPaintState) : esvg::Base(_parentPaintState) {
	
}

esvg::Ellipse::~Ellipse() {
	
}

bool esvg::Ellipse::parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax) {
	if (_element == nullptr) {
		return false;
	}
	parseTransform(_element);
	parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	m_transformMatrix *= _parentTrans;
	
	m_c.setValue(0,0);
	m_r.setValue(0,0);
	
	std::string content = _element->getAttribute("cx");
	if (content.size()!=0) {
		m_c.setX(parseLength(content));
	}
	content = _element->getAttribute("cy");
	if (content.size()!=0) {
		m_c.setY(parseLength(content));
	}
	content = _element->getAttribute("rx");
	if (content.size()!=0) {
		m_r.setX(parseLength(content));
	} else {
		SVG_ERROR("(l "<<_element->getPos()<<") Ellipse \"rx\" is not present");
		return false;
	}
	content = _element->getAttribute("ry");
	if (content.size()!=0) {
		m_r.setY(parseLength(content));
	} else {
		SVG_ERROR("(l "<<_element->getPos()<<") Ellipse \"ry\" is not present");
		return false;
	}
	_sizeMax.setValue(m_c.x() + m_r.x(), m_c.y() + m_r.y());
	
	return true;
}

void esvg::Ellipse::display(int32_t _spacing) {
	SVG_DEBUG(spacingDist(_spacing) << "Ellipse c=" << m_c << " r=" << m_r);
}


void esvg::Ellipse::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	SVG_VERBOSE(spacingDist(_level) << "DRAW esvg::Ellipse");
	/*
	_myRenderer.m_renderArea->color(agg::rgba8(m_paint.fill.r, m_paint.fill.g, m_paint.fill.b, m_paint.fill.a));
	// Creating an ellipse
	agg::ellipse myEllipse(m_c.x(), m_c.y(), m_r.x(), m_r.y(), 0);
	
	// Calculate transformation matrix ...
	mat2  mtx = m_transformMatrix;
	mtx *= _basicTrans;
	
	// set the filling mode : 
	_myRenderer.m_rasterizer.filling_rule((m_paint.flagEvenOdd)?agg::fill_even_odd:agg::fill_non_zero);
	
	if (m_paint.fill.a != 0x00) {
		agg::conv_transform<agg::ellipse, mat2> trans(myEllipse, mtx);
		_myRenderer.m_rasterizer.add_path(trans);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
	if (m_paint.strokeWidth > 0 && m_paint.stroke.a!=0x00 ) {
		_myRenderer.m_renderArea->color(agg::rgba8(m_paint.stroke.r, m_paint.stroke.g, m_paint.stroke.b, m_paint.stroke.a));
		// drawing as an outline
		agg::conv_stroke<agg::ellipse> myEllipseStroke(myEllipse);
		myEllipseStroke.width(m_paint.strokeWidth);
		agg::conv_transform<agg::conv_stroke<agg::ellipse>, mat2> transStroke(myEllipseStroke, mtx);
		// set the filling mode : 
		_myRenderer.m_rasterizer.filling_rule(agg::fill_non_zero);
		_myRenderer.m_rasterizer.add_path(transStroke);
		agg::render_scanlines(_myRenderer.m_rasterizer, _myRenderer.m_scanLine, *_myRenderer.m_renderArea);
	}
	*/
}



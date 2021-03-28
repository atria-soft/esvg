package org.atriasoft.esvg;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<esvg/Base.hpp>

namespace esvg{
class Ellipse extends esvg::Base
{
	private Vector2f c; //!< Center property of the ellipse
	private Vector2f r; //!< Radius property of the ellipse
	
	public Ellipse(final PaintState _parentPaintState) {
		super(_parentPaintState);
	}
	
	public boolean parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) override;
	
	public void display(final int _spacing) override;
	
	public void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) override;
	
	public void drawShapePoints(final List<List<Vector2f>> _out,
			                     final int _recurtionMax,
			                     final float _threshold,
			                     mat2x3& _basicTrans,
			                     int _level=1) override;
		private esvg::render::
	
	Path createPath();
};}

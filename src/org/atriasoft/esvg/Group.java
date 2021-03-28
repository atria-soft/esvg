package org.atriasoft.esvg;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<esvg/Base.hpp>#include<etk/Vector.hpp>

namespace esvg{
class Group extends esvg::Base
{
		private:
			List<ememory::SharedPtr<esvg::Base>> this.subElementList;  //!< sub elements ...
		public:
	
	Group(PaintState _parentPaintState);~
	
	Group();
	
	boolean parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) override;
	
	void display(final int spacing) override;
	
	void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) override;
	
	void drawShapePoints(final List<List<Vector2f>>& _out,
			                     int _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int _level=1) override;
	};
}

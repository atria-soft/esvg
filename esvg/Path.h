/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.h>
#include <esvg/render/Path.h>

namespace esvg {
	class Path : public esvg::Base {
		public:
			esvg::render::Path m_listElement;
		public:
			Path(PaintState _parentPaintState);
			~Path();
			virtual bool parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
}


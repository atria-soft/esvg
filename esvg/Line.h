/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <esvg/Base.h>

namespace esvg {
	class Line : public esvg::Base {
		private:
			vec2 m_startPos; //!< Start line position
			vec2 m_stopPos; //!< Stop line position
		public:
			Line(PaintState _parentPaintState);
			~Line();
			virtual bool parseXML(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
}


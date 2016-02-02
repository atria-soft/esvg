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
	class Circle : public esvg::Base {
		private:
			vec2 m_position; //!< Position of the Circle
			float m_radius; //!< Radius of the Circle
		public:
			Circle(PaintState _parentPaintState);
			~Circle();
			virtual bool parseXML(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
}



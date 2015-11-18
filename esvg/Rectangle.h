/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RECTANGLE_H__
#define __ESVG_RECTANGLE_H__

#include <esvg/Base.h>

namespace esvg {
	class Rectangle : public esvg::Base {
		private:
			vec2 m_position; //!< position of the rectangle
			vec2 m_size; //!< size of the rectangle
			vec2 m_roundedCorner; //!< property of the rounded corner
		public:
			Rectangle(PaintState _parentPaintState);
			~Rectangle();
			virtual bool parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
};

#endif


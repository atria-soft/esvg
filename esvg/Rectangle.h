/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_RECTANGLE_H__
#define __ESVG_RECTANGLE_H__

#include <esvg/Base.h>

namespace esvg
{
	class Rectangle : public esvg::Base
	{
		private:
			etk::Vector2D<float> m_position; //!< position of the rectangle
			etk::Vector2D<float> m_size; //!< size of the rectangle
			etk::Vector2D<float> m_roundedCorner; //!< property of the rounded corner
		public:
			Rectangle(PaintState _parentPaintState);
			~Rectangle(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t _spacing);
			virtual void AggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif

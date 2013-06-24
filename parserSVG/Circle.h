/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_CIRCLE_H__
#define __SVG_CIRCLE_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Circle : public svg::Base
	{
		private:
			etk::Vector2D<float> m_position; //!< Position of the Circle
			float m_radius; //!< Radius of the Circle
		public:
			Circle(PaintState _parentPaintState);
			~Circle(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t _spacing);
			virtual void AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


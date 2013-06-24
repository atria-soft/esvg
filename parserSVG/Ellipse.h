/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_ELLIPSE_H__
#define __SVG_ELLIPSE_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Ellipse : public svg::Base
	{
		private:
			etk::Vector2D<float> m_c;        //!< Center property of the ellipse
			etk::Vector2D<float> m_r;        //!< Radius property of the ellipse
		public:
			Ellipse(PaintState _parentPaintState);
			~Ellipse(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t _spacing);
			virtual void AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


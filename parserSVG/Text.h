/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_TEXT_H__
#define __SVG_TEXT_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Text : public svg::Base
	{
		private:
			
		public:
			Text(PaintState _parentPaintState);
			~Text(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t _spacing);
	};
};

#endif


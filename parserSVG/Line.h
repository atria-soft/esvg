/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_LINE_H__
#define __SVG_LINE_H__

#include <parserSVG/Base.h>

namespace svg
{
	class Line : public svg::Base
	{
		private:
			etk::Vector2D<float> m_startPos;       //!< Start line position
			etk::Vector2D<float> m_stopPos;        //!< Stop line position
		public:
			Line(PaintState parentPaintState);
			~Line(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& parentTrans, etk::Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
	};
};

#endif


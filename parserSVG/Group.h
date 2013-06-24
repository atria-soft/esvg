/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_GROUP_H__
#define __SVG_GROUP_H__

#include <parserSVG/Base.h>
#include <etk/Vector.h>

namespace svg
{
	class Group : public svg::Base
	{
		private:
			etk::Vector<svg::Base *> m_subElementList;  //!< group sub elements ...
		public:
			Group(PaintState _parentPaintState);
			~Group(void);
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


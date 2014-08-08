/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_LINE_H__
#define __ESVG_LINE_H__

#include <esvg/Base.h>

namespace esvg {
	class Line : public esvg::Base {
		private:
			etk::Vector2D<float> m_startPos; //!< Start line position
			etk::Vector2D<float> m_stopPos; //!< Stop line position
		public:
			Line(PaintState _parentPaintState);
			~Line();
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


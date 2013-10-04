/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_TEXT_H__
#define __ESVG_TEXT_H__

#include <esvg/Base.h>

namespace esvg {
	class Text : public esvg::Base {
		public:
			Text(PaintState _parentPaintState);
			~Text(void);
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void display(int32_t _spacing);
	};
};

#endif


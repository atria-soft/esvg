/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_GROUP_H__
#define __ESVG_GROUP_H__

#include <esvg/Base.h>
#include <vector>

namespace esvg {
	class Group : public esvg::Base {
		private:
			std::vector<esvg::Base *> m_subElementList;  //!< group sub elements ...
		public:
			Group(PaintState _parentPaintState);
			~Group();
			virtual bool parse(const std::shared_ptr<exml::Element>& _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void display(int32_t spacing);
			virtual void aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
	};
};

#endif


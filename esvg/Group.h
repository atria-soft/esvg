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
			virtual bool parseXML(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
};

#endif


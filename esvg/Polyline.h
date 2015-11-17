/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_POLYLINE_H__
#define __ESVG_POLYLINE_H__

#include <esvg/Base.h>
#include <vector>

namespace esvg {
	class Polyline : public esvg::Base {
		private:
			std::vector<vec2 > m_listPoint;    //!< list of all point of the polyline
		public:
			Polyline(PaintState _parentPaintState);
			~Polyline();
			virtual bool parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void aggDraw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
};

#endif


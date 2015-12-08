/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_LINEAR_GRANDIENT_H__
#define __ESVG_LINEAR_GRANDIENT_H__

#include <esvg/Base.h>

namespace esvg {
	class LinearGradient : public esvg::Base {
		private:
			esvg::Dimension m_pos1; //!< gradient position x1 y1
			esvg::Dimension m_pos2; //!< gradient position x2 y2
			std::vector<std::pair<float, etk::Color<float,4>>> m_data;
		public:
			LinearGradient(PaintState _parentPaintState);
			~LinearGradient();
			virtual bool parseXML(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
	};
};

#endif


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_PATH_H__
#define __ESVG_RENDER_PATH_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>
#include <esvg/render/Point.h>

namespace esvg {
	namespace render {
		class Path {
			public:
				std::vector<esvg::render::Element> m_listElement;
			public:
				Path() {
					
				}
				
				~Path() {
					
				}
				void clear();
				void stop(bool _relative);
				void moveTo(bool _relative, const vec2& _pos);
				void lineTo(bool _relative, const vec2& _pos);
				void lineToH(bool _relative, float _posX);
				void lineToV(bool _relative, float _posY);
				void curveTo(bool _relative, const vec2& _pos1, const vec2& _pos2, const vec2& _pos);
				void smoothCurveTo(bool _relative, const vec2& _pos2, const vec2& _pos);
				void bezierCurveTo(bool _relative, const vec2& _pos1, const vec2& _pos);
				void bezierSmoothCurveTo(bool _relative, const vec2& _pos);
				void ellipticTo(bool _relative, float _val0, float _val1, float _val2, float _val3, float _val4, float _val5, float _val6);
				void display(int32_t _spacing);
				std::vector<esvg::render::Point> generateListPoints(int32_t _level, int32_t _recurtionMax = 10, float _threshold = 0.25f);
		};
	}
}

#endif

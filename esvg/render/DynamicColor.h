/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_DYNAMIC_COLOR_H__
#define __ESVG_RENDER_DYNAMIC_COLOR_H__

#include <etk/types.h>
#include <etk/Color.h>
#include <etk/math/Vector2D.h>
#include <etk/math/Matrix2.h>

namespace esvg {
	namespace render {
		class DynamicColor {
			public:
				DynamicColor() {
					// nothing to do ...
				}
				virtual ~DynamicColor() {};
				virtual etk::Color<float,4> getColor(const ivec2& _pos) = 0;
		};
		class DynamicColorUni : public esvg::render::DynamicColor {
			public:
				etk::Color<float,4> m_color;
			public:
				DynamicColorUni(const etk::Color<float,4>& _color) :
				  m_color(_color) {
					
				}
				etk::Color<float,4> getColor(const ivec2& _pos) {
					return m_color;
				}
		};
		class DynamicColorLinear : public esvg::render::DynamicColor {
			public:
				etk::Color<float,4> m_color;
			public:
				DynamicColorLinear(const std::string& _link, const mat2& _mtx, const vec2 _objectSize, const vec2 _objectPos);
				etk::Color<float,4> getColor(const ivec2& _pos);
		};
		
		std::shared_ptr<DynamicColor> createColor(std::pair<etk::Color<float,4>, std::string> _color, const mat2& _mtx, const vec2 _size);
	}
}

#endif


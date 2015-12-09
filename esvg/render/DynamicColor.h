/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_DYNAMIC_COLOR_H__
#define __ESVG_RENDER_DYNAMIC_COLOR_H__

#include <memory>
#include <etk/types.h>
#include <etk/Color.h>
#include <etk/math/Vector2D.h>
#include <etk/math/Matrix2.h>

namespace esvg {
	class Document;
	namespace render {
		class DynamicColor {
			public:
				DynamicColor() {
					// nothing to do ...
				}
				virtual ~DynamicColor() {};
				virtual etk::Color<float,4> getColor(const ivec2& _pos) = 0;
				virtual void generate(esvg::Document* _document) = 0;
		};
		class DynamicColorUni : public esvg::render::DynamicColor {
			public:
				etk::Color<float,4> m_color;
			public:
				DynamicColorUni(const etk::Color<float,4>& _color) :
				  m_color(_color) {
					
				}
				virtual etk::Color<float,4> getColor(const ivec2& _pos) {
					return m_color;
				}
				virtual void generate(esvg::Document* _document) {
					// nothing to do ...
				}
		};
		class DynamicColorLinear : public esvg::render::DynamicColor {
			public:
				std::string m_colorName;
				mat2 m_matrix;
				vec2 m_size;
			public:
				DynamicColorLinear(const std::string& _link, const mat2& _mtx, const vec2 _size);
				virtual etk::Color<float,4> getColor(const ivec2& _pos);
				virtual void generate(esvg::Document* _document);
		};
		
		std::shared_ptr<DynamicColor> createColor(std::pair<etk::Color<float,4>, std::string> _color, const mat2& _mtx, const vec2 _size);
	}
}

#endif


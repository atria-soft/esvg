/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <ememory/memory.h>
#include <etk/types.h>
#include <etk/Color.h>
#include <etk/math/Vector2D.h>
#include <etk/math/Matrix2.h>
#include <esvg/gradientUnits.h>
#include <esvg/spreadMethod.h>

namespace esvg {
	class Document;
	namespace render {
		class DynamicColor {
			public:
				DynamicColor() {
					// nothing to do ...
				}
				virtual ~DynamicColor() {};
				virtual etk::Color<float,4> getColor(const ivec2& _pos) const = 0;
				virtual void generate(esvg::Document* _document) = 0;
				virtual void setViewPort(const std::pair<vec2, vec2>& _viewPort) = 0;
		};
		class DynamicColorUni : public esvg::render::DynamicColor {
			public:
				etk::Color<float,4> m_color;
			public:
				DynamicColorUni(const etk::Color<float,4>& _color) :
				  m_color(_color) {
					
				}
				virtual etk::Color<float,4> getColor(const ivec2& _pos) const {
					return m_color;
				}
				virtual void generate(esvg::Document* _document) {
					// nothing to do ...
				}
				virtual void setViewPort(const std::pair<vec2, vec2>& _viewPort) {
					// nothing to do ...
				};
		};
		class DynamicColorSpecial : public esvg::render::DynamicColor {
			public:
				bool m_linear;
				esvg::spreadMethod m_spread;
				esvg::gradientUnits m_unit;
				std::string m_colorName;
				mat2 m_matrix;
				std::pair<vec2, vec2> m_viewPort;
				vec2 m_pos1; // in radius ==> center
				vec2 m_pos2; // in radius ==> radius end position
				vec2 m_focal; // Specific radius
				vec2 m_axeX;
				vec2 m_axeY;
				vec2 m_baseSize;
				float m_focalLength;
				bool m_clipOut;
				bool m_centerIsFocal;
				std::vector<std::pair<float, etk::Color<float,4>>> m_data;
			public:
				DynamicColorSpecial(const std::string& _link, const mat2& _mtx);
				virtual etk::Color<float,4> getColor(const ivec2& _pos) const;
			private:
				etk::Color<float,4> getColorLinear(const ivec2& _pos) const;
				etk::Color<float,4> getColorRadial(const ivec2& _pos) const;
			public:
				virtual void generate(esvg::Document* _document);
				virtual void setViewPort(const std::pair<vec2, vec2>& _viewPort);
		};
		
		ememory::SharedPtr<DynamicColor> createColor(std::pair<etk::Color<float,4>, std::string> _color, const mat2& _mtx);
	}
}


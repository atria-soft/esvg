/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <ememory/memory.hpp>
#include <etk/types.hpp>
#include <etk/Pair.hpp>
#include <etk/Color.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/math/Matrix2x3.hpp>
#include <esvg/gradientUnits.hpp>
#include <esvg/spreadMethod.hpp>

namespace esvg {
	class Document;
	namespace render {
		class DynamicColor {
			public:
				DynamicColor() {
					// nothing to do ...
				}
				virtual ~DynamicColor() {};
				virtual etk::Color<float,4> getColor(const Vector2i& _pos) const = 0;
				virtual void generate(esvg::Document* _document) = 0;
				virtual void setViewPort(const etk::Pair<Vector2f, Vector2f>& _viewPort) = 0;
		};
		class DynamicColorUni : public esvg::render::DynamicColor {
			public:
				etk::Color<float,4> m_color;
			public:
				DynamicColorUni(const etk::Color<float,4>& _color) :
				  m_color(_color) {
					
				}
				virtual etk::Color<float,4> getColor(const Vector2i& _pos) const {
					return m_color;
				}
				virtual void generate(esvg::Document* _document) {
					// nothing to do ...
				}
				virtual void setViewPort(const etk::Pair<Vector2f, Vector2f>& _viewPort) {
					// nothing to do ...
				};
		};
		class DynamicColorSpecial : public esvg::render::DynamicColor {
			public:
				bool m_linear;
				esvg::spreadMethod m_spread;
				esvg::gradientUnits m_unit;
				etk::String m_colorName;
				mat2x3 m_matrix;
				etk::Pair<Vector2f, Vector2f> m_viewPort;
				Vector2f m_pos1; // in radius ==> center
				Vector2f m_pos2; // in radius ==> radius end position
				Vector2f m_focal; // Specific radius
				Vector2f m_axeX;
				Vector2f m_axeY;
				Vector2f m_baseSize;
				float m_focalLength;
				bool m_clipOut;
				bool m_centerIsFocal;
				List<etk::Pair<float, etk::Color<float,4>>> m_data;
			public:
				DynamicColorSpecial(const etk::String& _link, const mat2x3& _mtx);
				virtual etk::Color<float,4> getColor(const Vector2i& _pos) const;
			private:
				etk::Color<float,4> getColorLinear(const Vector2i& _pos) const;
				etk::Color<float,4> getColorRadial(const Vector2i& _pos) const;
			public:
				virtual void generate(esvg::Document* _document);
				virtual void setViewPort(const etk::Pair<Vector2f, Vector2f>& _viewPort);
		};
		
		ememory::SharedPtr<DynamicColor> createColor(etk::Pair<etk::Color<float,4>, etk::String> _color, const mat2x3& _mtx);
	}
}


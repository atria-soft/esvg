/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>

namespace esvg {
	namespace render {
		enum path {
			path_stop,
			path_close,
			path_moveTo,
			path_lineTo,
			path_lineToH,
			path_lineToV,
			path_curveTo,
			path_smoothCurveTo,
			path_bezierCurveTo,
			path_bezierSmoothCurveTo,
			path_elliptic
		};
		class Element {
			public:
				Element(enum path _type, bool _relative=false) :
				  m_cmd(_type),
				  m_relative(_relative) {
					
				}
				virtual ~Element() { }
			private:
				enum path m_cmd;
			public:
				enum path getType() const {
					return m_cmd;
				}
			protected:
				bool m_relative;
			public:
				bool getRelative() const {
					return m_relative;
				}
				void setRelative(bool _relative) {
					m_relative = _relative;
				}
			protected:
				vec2 m_pos;
			public:
				const vec2& getPos() const {
					return m_pos;
				}
				void setPos(const vec2& _val) {
					m_pos = _val;
				}
			protected:
				vec2 m_pos1;
			public:
				const vec2& getPos1() const {
					return m_pos1;
				}
				void setPos1(const vec2& _val) {
					m_pos1 = _val;
				}
			protected:
				vec2 m_pos2;
			public:
				const vec2& getPos2() const {
					return m_pos2;
				}
				void setPos2(const vec2& _val) {
					m_pos2 = _val;
				}
			public:
				virtual etk::String display() const = 0;
		};
	}
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::Stream& operator <<(etk::Stream& _os, const esvg::render::Element& _obj);
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::Stream& operator <<(etk::Stream& _os, enum esvg::render::path _obj);
}

#include <esvg/render/ElementStop.hpp>
#include <esvg/render/ElementClose.hpp>
#include <esvg/render/ElementMoveTo.hpp>
#include <esvg/render/ElementLineTo.hpp>
#include <esvg/render/ElementLineToH.hpp>
#include <esvg/render/ElementLineToV.hpp>
#include <esvg/render/ElementCurveTo.hpp>
#include <esvg/render/ElementSmoothCurveTo.hpp>
#include <esvg/render/ElementBezierCurveTo.hpp>
#include <esvg/render/ElementBezierSmoothCurveTo.hpp>
#include <esvg/render/ElementElliptic.hpp>


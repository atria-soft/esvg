/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_ELEMENT_H__
#define __ESVG_RENDER_ELEMENT_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>

namespace esvg {
	namespace render {
		enum path {
			path_stop,
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
				virtual std::string display() const = 0;
		};
	}
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, const esvg::render::Element& _obj);
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, enum esvg::render::path _obj);
}

#endif

#include <esvg/render/ElementStop.h>
#include <esvg/render/ElementMoveTo.h>
#include <esvg/render/ElementLineTo.h>
#include <esvg/render/ElementLineToH.h>
#include <esvg/render/ElementLineToV.h>
#include <esvg/render/ElementCurveTo.h>
#include <esvg/render/ElementSmoothCurveTo.h>
#include <esvg/render/ElementBezierCurveTo.h>
#include <esvg/render/ElementBezierSmoothCurveTo.h>
#include <esvg/render/ElementElliptic.h>


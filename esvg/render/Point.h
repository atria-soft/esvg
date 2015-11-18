/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDER_POINT_H__
#define __ESVG_RENDER_POINT_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <esvg/render/Element.h>

namespace esvg {
	namespace render {
		class Point {
			public:
				enum type {
					type_single, //!< Point type is single, this mean that it start and stop of a path
					type_start, //!< Point type is starting of a path
					type_stop, //!< Point type is stoping of a path
					type_join, //!< Point type in an user point provided inside a path
					type_interpolation, //!< This point is dynamicly calculated to create an interpolation
				};
			public:
				vec2 m_pos; //!< position of the point
				enum esvg::render::Point::type m_type;
				vec2 m_miterAxe;
				vec2 m_delta;
				float m_len;
				Point(const vec2& _pos, enum esvg::render::Point::type _type = esvg::render::Point::type_join) :
				  m_pos(_pos),
				  m_type(_type) {
					// nothing to do ...
				}
				void setEndPath() {
					if (m_type == esvg::render::Point::type_interpolation) {
						SVG_WARNING("Request stop path of an interpolate Point");
						m_type = esvg::render::Point::type_stop;
						return;
					}
					if (m_type == esvg::render::Point::type_stop) {
						SVG_WARNING("Request stop path of an STOP Point");
						return;
					}
					if (m_type == esvg::render::Point::type_start) {
						m_type = esvg::render::Point::type_single;
						return;
					}
					m_type = esvg::render::Point::type_stop;
				}
				void normalize(const vec2& _nextPoint) {
					m_delta = _nextPoint - m_pos;
					m_len = m_delta.length();
				}
		};
	}
}

#endif


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
				void setEndPath();
				void normalize(const vec2& _nextPoint);
		};
	}
}

#endif


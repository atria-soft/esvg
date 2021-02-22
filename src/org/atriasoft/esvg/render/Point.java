/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <esvg/render/Element.hpp>

namespace esvg {
	namespace render {
		class Point {
			public:
				enum class type {
					single, //!< Point type is single, this mean that it start and stop of a path
					start, //!< Point type is starting of a path
					stop, //!< Point type is stoping of a path
					join, //!< Point type in an user point provided inside a path
					interpolation, //!< This point is dynamicly calculated to create an interpolation
				};
			public:
				// TODO : Clean all element here ...
				Vector2f m_pos; //!< position of the point
				enum esvg::render::Point::type m_type;
				Vector2f m_miterAxe;
				Vector2f m_orthoAxePrevious;
				Vector2f m_orthoAxeNext;
				Vector2f m_posPrevious;
				Vector2f m_posNext;
				Vector2f m_delta;
				float m_len;
				// TODO: Update List to support not having it ...
				Point() :
				  m_pos(0,0),
				  m_type(esvg::render::Point::type::join) {
					// nothing to do ...
				}
				Point(const Vector2f& _pos, enum esvg::render::Point::type _type = esvg::render::Point::type::join) :
				  m_pos(_pos),
				  m_type(_type) {
					// nothing to do ...
				}
				void setEndPath();
				void normalize(const Vector2f& _nextPoint);
		};
	}
}


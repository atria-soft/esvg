package org.atriasoft.esvg.render;
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
				Vector2f this.pos; //!< position of the point
				enum esvg::render::Point::type this.type;
				Vector2f this.miterAxe;
				Vector2f this.orthoAxePrevious;
				Vector2f this.orthoAxeNext;
				Vector2f this.posPrevious;
				Vector2f this.posNext;
				Vector2f this.delta;
				float this.len;
				// TODO: Update List to support not having it ...
				Point() :
				  this.pos(0,0),
				  this.type(esvg::render::Point::type::join) {
					// nothing to do ...
				}
				Point(const Vector2f& _pos, enum esvg::render::Point::type _type = esvg::render::Point::type::join) :
				  this.pos(_pos),
				  this.type(_type) {
					// nothing to do ...
				}
				void setEndPath();
				void normalize(const Vector2f& _nextPoint);
		};
	}
}


package org.atriasoft.esvg.render;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/math/Vector2D.hpp>

namespace esvg{namespace render{
class Element {
	public:
				Element(enum path _type, boolean _relative=false) :
				  this.cmd(_type),
				  this.relative(_relative) {
					
				}
				virtual ~Element() { }
			private:
				enum path this.cmd;
			public:
				enum path getType() const {
					return this.cmd;
				}
			protected:
				boolean this.relative;
			public:
				boolean getRelative() const {
					return this.relative;
				}
				void setRelative(boolean _relative) {
					this.relative = _relative;
				}
			protected:
				Vector2f this.pos;
			public:
				const Vector2f& getPos() const {
					return this.pos;
				}
				void setPos(const Vector2f& _val) {
					this.pos = _val;
				}
			protected:
				Vector2f this.pos1;
			public:
				const Vector2f& getPos1() const {
					return this.pos1;
				}
				void setPos1(const Vector2f& _val) {
					this.pos1 = _val;
				}
			protected:
				Vector2f this.pos2;
			public:
				const Vector2f& getPos2() const {
					return this.pos2;
				}
				void setPos2(const Vector2f& _val) {
					this.pos2 = _val;
				}
			public:
				virtual etk::String display() const = 0;
		};
	}
	/**
	 * Debug operator To display the curent element in a Human redeable information
	 */
	etk::Stream& operator <<(etk::Stream& _os, const esvg::render::Element& _obj);
	/**
	 * Debug operator To display the curent element in a Human redeable information
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

;
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
		}
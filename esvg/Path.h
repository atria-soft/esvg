/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_PATH_H__
#define __ESVG_PATH_H__

#include <esvg/Base.h>
#include <agg/agg_path_storage.h>

namespace esvg {
	enum pathProperty{
		pathStop,
		pathMoveTo,
		pathLineTo,
		pathLineToH,
		pathLineToV,
		pathCurveTo,
		pathSmothCurveTo,
		pathBesizeCurveTo,
		pathBesizeSmothCurveTo,
		pathElliptic
	};
	class PathBasic {
		public:
			PathBasic(void) : m_cmd(esvg::pathStop), m_relative(false) {
				for(int32_t iii=0; iii<7; ++iii) {
					m_element[iii] = 0;
				}
			}
			enum pathProperty m_cmd;
			bool m_relative;
			float m_element[7];
	};
	class Path : public esvg::Base {
		private:
			std::vector<PathBasic> m_listElement;
		public:
			Path(PaintState _parentPaintState);
			~Path(void);
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
		private:
			void abstractMoveTo(agg::path_storage& _path, bool _rel, double _x, double _y);
			void abstractLineTo(agg::path_storage& _path, bool _rel, double _x, double _y);
			void abstractHLineTo(agg::path_storage& _path, bool _rel, double _x);
			void abstractVLineTo(agg::path_storage& _path, bool _rel, double _y);
			void abstractCurve3(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x, double _y);
			void abstractCurve3(agg::path_storage& _path, bool _rel, double _x, double _y);
			void abstractCurve4(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x2, double _y2, double _x, double _y);
			void abstractCurve4(agg::path_storage& _path, bool _rel, double _x2, double _y2, double _x, double _y);
			void abstractCloseSubpath(agg::path_storage& _path);
	};
};

#endif


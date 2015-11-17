/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_PATH_H__
#define __ESVG_PATH_H__

#include <esvg/Base.h>
#include <esvg/RenderPath.h>

namespace esvg {
	enum pathProperty{
		path_stop,
		path_moveTo,
		path_lineTo,
		path_lineToH,
		path_lineToV,
		path_curveTo,
		path_smothCurveTo,
		path_bezierCurveTo,
		path_bezierSmothCurveTo,
		path_elliptic
	};
	class PathBasic {
		public:
			PathBasic() : m_cmd(esvg::path_stop), m_relative(false) {
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
			~Path();
			virtual bool parse(const std::shared_ptr<exml::Element>& _element, mat2& _parentTrans, vec2& _sizeMax);
			virtual void display(int32_t _spacing);
			virtual void aggDraw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level);
		private:
			void abstractMoveTo(esvg::RenderPath& _path, bool _rel, double _x, double _y);
			void abstractLineTo(esvg::RenderPath& _path, bool _rel, double _x, double _y);
			void abstractHLineTo(esvg::RenderPath& _path, bool _rel, double _x);
			void abstractVLineTo(esvg::RenderPath& _path, bool _rel, double _y);
			void abstractCurve3(esvg::RenderPath& _path, bool _rel, double _x1, double _y1, double _x, double _y);
			void abstractCurve3(esvg::RenderPath& _path, bool _rel, double _x, double _y);
			void abstractCurve4(esvg::RenderPath& _path, bool _rel, double _x1, double _y1, double _x2, double _y2, double _x, double _y);
			void abstractCurve4(esvg::RenderPath& _path, bool _rel, double _x2, double _y2, double _x, double _y);
			void abstractCloseSubpath(esvg::RenderPath& _path);
	};
};

#endif


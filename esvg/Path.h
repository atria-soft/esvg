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

namespace esvg
{
	typedef enum {
		PATH_ENUM_STOP,
		PATH_ENUM_MOVETO,
		PATH_ENUM_LINETO,
		PATH_ENUM_LINETO_H,
		PATH_ENUM_LINETO_V,
		PATH_ENUM_CURVETO,
		PATH_ENUM_SMOTH_CURVETO,
		PATH_ENUM_BEZIER_CURVETO,
		PATH_ENUM_BEZIER_SMOTH_CURVETO,
		PATH_ENUM_ELLIPTIC,
	} pathEnum_te;
	
	typedef struct {
		pathEnum_te cmd;
		bool        relative;
		float       element[7];
	}pathBasic_ts;
	
	class Path : public esvg::Base
	{
		private:
			etk::Vector<pathBasic_ts> m_listElement;
		public:
			Path(PaintState _parentPaintState);
			~Path(void);
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			virtual void Display(int32_t _spacing);
			virtual void AggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
		private:
			void AbstractMoveTo(agg::path_storage& _path, bool _rel, double _x, double _y);
			void AbstractLineTo(agg::path_storage& _path, bool _rel, double _x, double _y);
			void AbstractHLineTo(agg::path_storage& _path, bool _rel, double _x);
			void AbstractVLineTo(agg::path_storage& _path, bool _rel, double _y);
			void AbstractCurve3(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x, double _y);
			void AbstractCurve3(agg::path_storage& _path, bool _rel, double _x, double _y);
			void AbstractCurve4(agg::path_storage& _path, bool _rel, double _x1, double _y1, double _x2, double _y2, double _x, double _y);
			void AbstractCurve4(agg::path_storage& _path, bool _rel, double _x2, double _y2, double _x, double _y);
			void AbstractCloseSubpath(agg::path_storage& _path);
	};
};

#endif


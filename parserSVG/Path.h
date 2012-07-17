/**
 *******************************************************************************
 * @file parserSVG/Path.h
 * @brief basic path parsing (Header)
 * @author Edouard DUPIN
 * @date 20/03/2012
 * @par Project
 * parserSVG
 *
 * @par Copyright
 * Copyright 2011 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */

#ifndef __SVG_PATH_H__
#define __SVG_PATH_H__

#include <parserSVG/Base.h>
#include <agg/agg_path_storage.h>

namespace svg
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
	
	class Path : public svg::Base
	{
		private:
			etk::VectorType<pathBasic_ts> m_listElement;
		public:
			Path(PaintState parentPaintState);
			~Path(void);
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax);
			virtual void Display(int32_t spacing);
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans);
		private:
			void AbstractMoveTo(agg::path_storage& path, bool rel, double x, double y);
			void AbstractLineTo(agg::path_storage& path, bool rel, double x, double y);
			void AbstractHLineTo(agg::path_storage& path, bool rel, double x);
			void AbstractVLineTo(agg::path_storage& path, bool rel, double y);
			void AbstractCurve3(agg::path_storage& path, bool rel, double x1, double y1, double x, double y);
			void AbstractCurve3(agg::path_storage& path, bool rel, double x, double y);
			void AbstractCurve4(agg::path_storage& path, bool rel, double x1, double y1, double x2, double y2, double x,  double y);
			void AbstractCurve4(agg::path_storage& path, bool rel, double x2, double y2, double x, double y);
			void AbstractCloseSubpath(agg::path_storage& path);
	};
};

#endif


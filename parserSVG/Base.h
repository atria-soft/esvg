/**
 *******************************************************************************
 * @file parserSVG/Base.h
 * @brief basic Element parsing (Header)
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

#ifndef __SVG_BASE_H__
#define __SVG_BASE_H__

#include <etk/Types.h>
#include <etk/Vector.h>
#include <draw/Color.h>

#include <tinyXML/tinyxml.h>
#include <parserSVG/Renderer.h>

#include <agg/agg_basics.h>
#include <agg/agg_rendering_buffer.h>
#include <agg/agg_rasterizer_scanline_aa.h>
#include <agg/agg_scanline_p.h>
#include <agg/agg_renderer_scanline.h>
#include <agg/agg_path_storage.h>
#include <agg/agg_conv_transform.h>
#include <agg/agg_bounding_rect.h>
#include <agg/agg_color_rgba.h>
#include <agg/agg_pixfmt_rgba.h>

namespace svg
{
	class Base
	{
		protected:
			PaintState         m_paint;
			agg::trans_affine  m_transformMatrix; //!< specific render of the curent element
			const char * SpacingDist(int32_t spacing);
		public:
			Base(void) {};
			Base(PaintState parentPaintState);
			virtual ~Base(void) { };
			virtual bool Parse(TiXmlNode * node, agg::trans_affine& parentTrans, Vector2D<float>& sizeMax);
			//specific drawing for AAG librairy ...
			virtual void AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans) { };
			
			virtual void Display(int32_t spacing) { };
			void ParseTransform(TiXmlNode *node);
			void ParsePosition(const TiXmlNode *node, Vector2D<float> &pos, Vector2D<float> &size);
			float ParseLength(const char *dataInput);
			void ParsePaintAttr(const TiXmlNode *node);
			draw::Color ParseColor(const char *inputData);
	};
};

#endif


/**
 *******************************************************************************
 * @file parserSVG/Renderer.h
 * @brief Basic SVG renderer for the AGG librairy (Header)
 * @author Edouard DUPIN
 * @date 23/03/2012
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

#ifndef __SVG_RENDERER_H__
#define __SVG_RENDERER_H__

#include <etk/UString.h>
#include <etk/Color.h>

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
	typedef enum {
		LINECAP_BUTT,
		LINECAP_ROUND,
		LINECAP_SQUARE,
	} lineCap_te;
	typedef enum {
		LINEJOIN_MITER,
		LINEJOIN_ROUND,
		LINEJOIN_BEVEL,
	} lineJoin_te;
	
	class PaintState {
		public:
			etk::Color        fill;
			etk::Color        stroke;
			float             strokeWidth;
			bool              flagEvenOdd;
			lineCap_te        lineCap;
			lineJoin_te       lineJoin;
			Vector2D<float>   viewPort;
	};
	
	// basic definition type for the renderer
	typedef agg::renderer_base<agg::pixfmt_rgba32>           rendererBase_t;
	typedef agg::renderer_scanline_aa_solid<rendererBase_t>  rendererSolid_t;
	
	class Renderer {
		private:
			uint8_t *                     m_buffer;
			uint32_t                      m_allocatedSize;
		public:
			Renderer(uint32_t width, uint32_t height);
			~Renderer(void);
			void WritePpm(etk::UString fileName);
			Vector2D<float>               m_size;
			agg::rendering_buffer *       m_renderingBuffer;
			agg::pixfmt_rgba32 *          m_pixFrame;
			rendererBase_t *              m_renderBase;
			rendererSolid_t *             m_renderArea;
			agg::rasterizer_scanline_aa<> m_rasterizer;  //!< AGG renderer system
			agg::scanline_p8              m_scanLine;    //!< 
			uint8_t* GetDataPointer(void) { return m_buffer; };
			uint32_t GetDataSize(void)    { return m_allocatedSize; };
	};
};

#endif

/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_RENDERER_H__
#define __ESVG_RENDERER_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <draw/Color.h>

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

namespace esvg {
	enum lineCap{
		lineCapButt,
		lineCapRound,
		lineCapSquare
	};
	enum lineJoin{
		lineJoinMiter,
		lineJoinRound,
		lineJoinBevel
	};
	
	class PaintState {
		public:
			draw::Color fill;
			draw::Color stroke;
			float strokeWidth;
			bool flagEvenOdd;
			enum esvg::lineCap lineCap;
			enum esvg::lineJoin lineJoin;
			etk::Vector2D<float> viewPort;
	};
	
	// basic definition type for the renderer
	typedef agg::renderer_base<agg::pixfmt_rgba32> rendererBase_t;
	typedef agg::renderer_scanline_aa_solid<rendererBase_t> rendererSolid_t;
	
	class Renderer {
		private:
			uint8_t * m_buffer;
			uint32_t m_allocatedSize;
		public:
			Renderer(uint32_t width, uint32_t height);
			~Renderer(void);
			void writePpm(std::string fileName);
			etk::Vector2D<float> m_size;
			agg::rendering_buffer * m_renderingBuffer;
			agg::pixfmt_rgba32 * m_pixFrame;
			rendererBase_t * m_renderBase;
			rendererSolid_t * m_renderArea;
			agg::rasterizer_scanline_aa<> m_rasterizer;  //!< AGG renderer system
			agg::scanline_p8 m_scanLine;    //!< 
			uint8_t* getDataPointer(void) { return m_buffer; };
			uint32_t getDataSize(void) { return m_allocatedSize; };
	};
};

#endif

/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_BASE_H__
#define __ESVG_BASE_H__

#include <etk/types.h>
#include <etk/Vector.h>
#include <etk/math/Vector2D.h>
#include <draw/Color.h>

#include <exml/exml.h>
#include <esvg/Renderer.h>

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

namespace esvg
{
	class Base
	{
		protected:
			PaintState         m_paint;
			agg::trans_affine  m_transformMatrix; //!< specific render of the curent element
			const char * SpacingDist(int32_t _spacing);
		public:
			Base(void) {};
			Base(PaintState _parentPaintState);
			virtual ~Base(void) { };
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			//specific drawing for AAG librairy ...
			virtual void AggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans) { };
			
			virtual void Display(int32_t _spacing) { };
			void parseTransform(exml::Element *_element);
			void parsePosition(const exml::Element *_element, etk::Vector2D<float> &_pos, etk::Vector2D<float> &_size);
			float parseLength(const etk::UString& _dataInput);
			void parsePaintAttr(const exml::Element *_element);
			draw::Color parseColor(const etk::UString& _inputData);
	};
};

#endif


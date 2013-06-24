/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_BASE_H__
#define __SVG_BASE_H__

#include <etk/types.h>
#include <etk/Vector.h>
#include <etk/math/Vector2D.h>
#include <draw/Color.h>

#include <exml/exml.h>
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
			const char * SpacingDist(int32_t _spacing);
		public:
			Base(void) {};
			Base(PaintState _parentPaintState);
			virtual ~Base(void) { };
			virtual bool Parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			//specific drawing for AAG librairy ...
			virtual void AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans) { };
			
			virtual void Display(int32_t _spacing) { };
			void ParseTransform(exml::Element *_element);
			void ParsePosition(const exml::Element *_element, etk::Vector2D<float> &_pos, etk::Vector2D<float> &_size);
			float ParseLength(const etk::UString& _dataInput);
			void ParsePaintAttr(const exml::Element *_element);
			draw::Color ParseColor(const etk::UString& _inputData);
	};
};

#endif


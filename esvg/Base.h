/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_BASE_H__
#define __ESVG_BASE_H__

#include <etk/types.h>
#include <vector>
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

namespace esvg {
	class Base {
		protected:
			PaintState m_paint;
			agg::trans_affine m_transformMatrix; //!< specific render of the curent element
			const char * spacingDist(int32_t _spacing);
		public:
			Base() {};
			Base(PaintState _parentPaintState);
			virtual ~Base() { };
			virtual bool parse(exml::Element * _element, agg::trans_affine& _parentTrans, etk::Vector2D<float>& _sizeMax);
			//specific drawing for AAG librairy ...
			virtual void aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans) { };
			
			virtual void display(int32_t _spacing) { };
			void parseTransform(exml::Element *_element);
			void parsePosition(const exml::Element *_element, etk::Vector2D<float> &_pos, etk::Vector2D<float> &_size);
			float parseLength(const std::string& _dataInput);
			void parsePaintAttr(const exml::Element *_element);
			draw::Color parseColor(const std::string& _inputData);
	};
};

#endif


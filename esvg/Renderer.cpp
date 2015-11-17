/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Renderer.h>

// 4 is for the RGBA ...
#define DATA_ALLOCATION_ELEMENT (4)

#undef __class__
#define __class__ "Renderer"

esvg::Renderer::Renderer(const ivec2& _size) {
	m_size = _size;
	m_stride = DATA_ALLOCATION_ELEMENT;
	m_scanline.resize(m_size.x() * m_stride, 0);
	m_buffer.resize(m_size.x() * m_size.y() * m_stride, 0);
}

esvg::Renderer::~Renderer() {
	m_buffer.clear();
	m_scanline.clear();
	m_stride = 0;
	m_size = ivec2(0,0);
}

/*
void nsvgRasterize(NSVGrasterizer* rrr, // this
				   NSVGimage* image, // image definition
				   float tx, // move x
				   float ty, // move y
				   float scale, // scale
				   unsigned char* dst, //output image data
				   int w, // output width
				   int h, // output height
				   int stride) // pixel stride
{
	NSVGshape *shape = NULL;
	NSVGedge *eee = NULL;
	NSVGcachedPaint cache;
	int i;

	rrr->bitmap = dst;
	rrr->width = w;
	rrr->height = h;
	rrr->stride = stride;

	if (w > rrr->cscanline) {
		rrr->cscanline = w;
		rrr->scanline = (unsigned char*)realloc(rrr->scanline, w);
		if (rrr->scanline == NULL) return;
	}

	for (i = 0; i < h; i++)
		memset(&dst[i*stride], 0, w*4);

	for (shape = image->shapes;
	     shape != NULL;
	     shape = shape->next) {
		if (!(shape->flags & NSVG_FLAGS_VISIBLE))
			continue;
		// ***********************
		// *** render "fill" *****
		// ***********************
		if (shape->fill.type != NSVG_PAINT_NONE) {
			nsvg__resetPool(rrr);
			rrr->freelist = NULL;
			rrr->nedges = 0;
			nsvg__flattenShape(rrr, shape, scale);
			// Scale and translate edges
			for (i = 0; i < r->nedges; i++) {
				eee = &rrr->edges[i];
				eee->x0 = tx + eee->x0;
				eee->y0 = (ty + eee->y0) * NSVG__SUBSAMPLES;
				eee->x1 = tx + eee->x1;
				eee->y1 = (ty + eee->y1) * NSVG__SUBSAMPLES;
			}
			// Rasterize edges
			qsort(rrr->edges,
			      rrr->nedges,
			      sizeof(NSVGedge),
			      nsvg__cmpEdge);
			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			nsvg__initPaint(&cache,
			                &shape->fill,
			                shape->opacity);
			nsvg__rasterizeSortedEdges(rrr,
			                           tx,
			                           ty,
			                           scale,
			                           &cache,
			                           shape->fillRule);
		}
		// *************************
		// *** render "stroke" *****
		// *************************
		if (    shape->stroke.type != NSVG_PAINT_NONE
		     && (shape->strokeWidth * scale) > 0.01f) {
			nsvg__resetPool(r);
			rrr->freelist = NULL;
			rrr->nedges = 0;
			nsvg__flattenShapeStroke(rrr, shape, scale);
//			dumpEdges(r, "edge.svg");
			// Scale and translate edges
			for (i = 0; i < rrr->nedges; i++) {
				eee = &rrr->edges[i];
				eee->x0 = tx + eee->x0;
				eee->y0 = (ty + eee->y0) * NSVG__SUBSAMPLES;
				eee->x1 = tx + eee->x1;
				eee->y1 = (ty + eee->y1) * NSVG__SUBSAMPLES;
			}
			// Rasterize edges
			qsort(rrr->edges,
			      rrr->nedges,
			      sizeof(NSVGedge),
			      nsvg__cmpEdge);
			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			nsvg__initPaint(&cache,
			                &shape->stroke,
			                shape->opacity);
			nsvg__rasterizeSortedEdges(rrr,
			                           tx,
			                           ty,
			                           scale,
			                           &cache,
			                           NSVG_FILLRULE_NONZERO);
		}
	}
	nsvg__unpremultiplyAlpha(dst,
	                         w,
	                         h,
	                         stride);
	rrr->bitmap = NULL;
	rrr->width = 0;
	rrr->height = 0;
	rrr->stride = 0;
}
*/

// Writing the buffer to a .PPM file, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
void esvg::Renderer::writePpm(std::string fileName) {
	if (m_buffer.size() == 0) {
		return;
	}
	FILE* fd = fopen(fileName.c_str(), "wb");
	if(NULL != fd) {
		int32_t sizeX = m_size.x();
		int32_t sizeY = m_size.y();
		SVG_DEBUG("Generate ppm : " << m_size);
		fprintf(fd, "P6 %d %d 255 ", sizeX, sizeY);
		for (int32_t iii=0 ; iii<sizeX*sizeY; iii++) {
			fwrite(&m_buffer[iii*DATA_ALLOCATION_ELEMENT], 1, 3, fd);
		}
		fclose(fd);
	}
}





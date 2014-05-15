/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/Renderer.h>

// 4 is for the RGBA ...
#define DATA_ALLOCATION_ELEMENT (4)

#undef __class__
#define __class__ "Renderer"

esvg::Renderer::Renderer(uint32_t width, uint32_t height) {
	m_allocatedSize = 0;
	m_size.setValue(width, height);
	
	int32_t dataSize = ((int32_t)width * (int32_t)height * DATA_ALLOCATION_ELEMENT);
	m_allocatedSize = dataSize;
	
	// allocate Data
	SVG_VERBOSE("Allocate buffer : " << dataSize);
	
	m_buffer = new uint8_t[dataSize];
	if (NULL == m_buffer) {
		SVG_ERROR("Allocation of the output buffer for SVG drawing error");
		m_allocatedSize = 0;
		return;
	}
	
	memset(m_buffer, 0x00, dataSize * sizeof(uint8_t) );

	m_renderingBuffer = new agg::rendering_buffer(m_buffer, m_size.x(), m_size.y(), m_size.x() * DATA_ALLOCATION_ELEMENT);
	if (NULL == m_renderingBuffer) {
		SVG_ERROR("Allocation of the m_renderingBuffer for SVG drawing error");
		return;
	}
	
	m_pixFrame        = new agg::pixfmt_rgba32(*m_renderingBuffer);
	if (NULL == m_pixFrame) {
		SVG_ERROR("Allocation of the m_pixFrame for SVG drawing error");
		return;
	}
	
	m_renderBase      = new rendererBase_t(*m_pixFrame);
	if (NULL == m_renderBase) {
		SVG_ERROR("Allocation of the m_renderBase for SVG drawing error");
		return;
	}
	
	m_renderArea      = new rendererSolid_t(*m_renderBase);
	if (NULL == m_renderArea) {
		SVG_ERROR("Allocation of the m_renderArea for SVG drawing error");
		return;
	}
	
	//m_basicMatrix *= agg::trans_affine_translation(-g_base_dx2, -g_base_dy2);
	//m_basicMatrix *= agg::trans_affine_scaling(g_scale*coefmult, g_scale*coefmult);
	//m_basicMatrix *= agg::trans_affine_rotation(g_angle);// + agg::pi);
	//m_basicMatrix *= agg::trans_affine_skewing(g_skew_x/1000.0, g_skew_y/1000.0);
	//m_basicMatrix *= agg::trans_affine_translation(m_size.x*0.7, m_size.y/2);
}

esvg::Renderer::~Renderer() {
	if (NULL != m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}
}

// Writing the buffer to a .PPM file, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
void esvg::Renderer::writePpm(std::string fileName) {
	if (NULL == m_buffer) {
		return;
	}
	FILE* fd = fopen(fileName.c_str(), "wb");
	if(NULL != fd) {
		int32_t sizeX = m_size.x();
		int32_t sizeY = m_size.y();
		SVG_DEBUG("Generate ppm : " << m_size);
		fprintf(fd, "P6 %d %d 255 ", sizeX, sizeY);
		for (int32_t iii=0 ; iii<sizeX*sizeY; iii++) {
			fwrite(m_buffer+iii*DATA_ALLOCATION_ELEMENT, 1, 3, fd);
		}
		fclose(fd);
	}
}



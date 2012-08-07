/**
 *******************************************************************************
 * @file parserSVG/Renderer.cpp
 * @brief Basic SVG renderer for the AGG librairy (Sources)
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

#include <etk/Types.h>
#include <etk/Memory.h>
#include <parserSVG/Debug.h>
#include <parserSVG/Renderer.h>

// 4 is for the RGBA ...
#define DATA_ALLOCATION_ELEMENT        (4)

svg::Renderer::Renderer(uint32_t width, uint32_t height)
{
	m_allocatedSize = 0;
	m_size.x = width;
	m_size.y = height;
	
	int32_t dataSize = ((int32_t)width * (int32_t)height * DATA_ALLOCATION_ELEMENT);
	m_allocatedSize = dataSize;
	
	// allocate Data
	SVG_DEBUG("Allocate buffer : " << dataSize);
	
	ETK_MALLOC(m_buffer, dataSize, uint8_t);
	if (NULL == m_buffer) {
		SVG_ERROR("Allocation of the output buffer for SVG drawing error");
		m_allocatedSize = 0;
		return;
	}
	
	memset(m_buffer, 0x00, dataSize * sizeof(uint8_t) );

	m_renderingBuffer = new agg::rendering_buffer(m_buffer, m_size.x, m_size.y, m_size.x * DATA_ALLOCATION_ELEMENT);
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

svg::Renderer::~Renderer(void)
{
	if (NULL != m_buffer) {
		ETK_FREE(m_buffer);
		m_buffer = NULL;
	}
}

// Writing the buffer to a .PPM file, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
void svg::Renderer::WritePpm(etk::UString fileName)
{
	if (NULL == m_buffer) {
		return;
	}
	FILE* fd = fopen(fileName.Utf8Data(), "wb");
	if(NULL != fd) {
		int32_t sizeX = m_size.x;
		int32_t sizeY = m_size.y;
		SVG_DEBUG("Generate ppm : " << m_size);
		fprintf(fd, "P6 %d %d 255 ", sizeX, sizeY);
		for (int32_t iii=0 ; iii<sizeX*sizeY; iii++) {
			fwrite(m_buffer+iii*DATA_ALLOCATION_ELEMENT, 1, 3, fd);
		}
		fclose(fd);
	}
}
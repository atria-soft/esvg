/**
 *******************************************************************************
 * @file parserSVG/parserSVG.cpp
 * @brief parserSVG : basic header of the SVG parser (Sources)
 * @author Edouard DUPIN
 * @date 18/03/2012
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

#include <parserSVG/Debug.h>
#include <parserSVG/parserSVG.h>
#include <tinyXML/tinyxml.h>
#include <parserSVG/Base.h>
#include <parserSVG/Circle.h>
#include <parserSVG/Ellipse.h>
#include <parserSVG/Line.h>
#include <parserSVG/Path.h>
#include <parserSVG/Polygon.h>
#include <parserSVG/Polyline.h>
#include <parserSVG/Rectangle.h>
#include <parserSVG/Text.h>
#include <parserSVG/Group.h>

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

svg::Parser::Parser(etk::FSNode fileName) : m_renderedElement(NULL)
{
	m_fileName = fileName;
	m_version = "0.0";
	m_loadOK = true;
	m_paint.fill = (int32_t)0xFF0000FF;
	m_paint.stroke = (int32_t)0xFFFFFF00;
	
	m_paint.strokeWidth = 1.0;
	m_paint.viewPort.x = 255;
	m_paint.viewPort.y = 255;
	m_paint.flagEvenOdd = false;
	m_paint.lineJoin = svg::LINEJOIN_MITER;
	m_paint.lineCap = svg::LINECAP_BUTT;
	m_size.x = 0.0;
	m_size.y = 0.0;
	
	// Start loading the XML : 
	SVG_DEBUG("open file (SVG) \"" << m_fileName << "\"");

	// allocate the document in the stack
	TiXmlDocument XmlDocument;
	if (false == m_fileName.Exist()) {
		SVG_ERROR("File Does not exist : " << m_fileName);
		m_loadOK = false;
		return;
	}
	int32_t fileSize = m_fileName.FileSize();
	if (0==fileSize) {
		SVG_ERROR("This file is empty : " << m_fileName);
		m_loadOK = false;
		return;
	}
	if (false == m_fileName.FileOpenRead()) {
		SVG_ERROR("Can not open the file : " << m_fileName);
		m_loadOK = false;
		return;
	}
	// allocate data
	char * fileBuffer = new char[fileSize+5];
	if (NULL == fileBuffer) {
		SVG_ERROR("Error Memory allocation size=" << fileSize);
		m_loadOK = false;
		return;
	}
	memset(fileBuffer, 0, (fileSize+5)*sizeof(char));
	// load data from the file :
	m_fileName.FileRead(fileBuffer, 1, fileSize);
	// close the file:
	m_fileName.FileClose();
	// load the XML from the memory
	XmlDocument.Parse((const char*)fileBuffer, 0, TIXML_ENCODING_UTF8);

	TiXmlElement* root = XmlDocument.FirstChildElement( "svg" );
	if (NULL == root ) {
		SVG_ERROR("(l ?) main node not find: \"svg\" in \"" << m_fileName << "\"");
		m_loadOK = false;
	} else {
		// get the svg version :
		const char *version = root->ToElement()->Attribute("version");
		if (NULL != version) {
			m_version = version;
		}
		// parse ...
		etk::Vector2D<float> pos;
		ParseTransform(root);
		ParsePosition(root, pos, m_size);
		ParsePaintAttr(root);
		SVG_VERBOSE("parsed .ROOT trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
		
		
		etk::Vector2D<float> maxSize;
		maxSize.x = 0.0;
		maxSize.y = 0.0;
		
		etk::Vector2D<float> size;
		// parse all sub node :
		for(TiXmlNode * child = root->FirstChild(); NULL != child; child = child->NextSibling() ) {
			svg::Base *elementParser = NULL;
			if (child->Type()==TiXmlNode::TINYXML_COMMENT) {
				// nothing to do, just proceed to next step
			} else {
				etk::UString localValue = child->Value();
				bool normalNoElement = false;
				if (localValue == "g") {
					elementParser = new svg::Group(m_paint);
				} else if (localValue == "a") {
					SVG_INFO("Note : 'a' balise is parsed like a g balise ...");
					elementParser = new svg::Group(m_paint);
				} else if (localValue == "title") {
					m_title = "TODO : set the title here ...";
					normalNoElement = true;
				} else if (localValue == "path") {
					elementParser = new svg::Path(m_paint);
				} else if (localValue == "rect") {
					elementParser = new svg::Rectangle(m_paint);
				} else if (localValue == "circle") {
					elementParser = new svg::Circle(m_paint);
				} else if (localValue == "ellipse") {
					elementParser = new svg::Ellipse(m_paint);
				} else if (localValue == "line") {
					elementParser = new svg::Line(m_paint);
				} else if (localValue == "polyline") {
					elementParser = new svg::Polyline(m_paint);
				} else if (localValue == "polygon") {
					elementParser = new svg::Polygon(m_paint);
				} else if (localValue == "text") {
					elementParser = new svg::Text(m_paint);
				} else if (localValue == "metadata") {
					// nothing to do : generaly inkscape data
					normalNoElement = true;
				} else {
					SVG_ERROR("(l "<<child->Row()<<") node not suported : \""<<localValue<<"\" must be [title,g,a,path,rect,circle,ellipse,line,polyline,polygon,text,metadata]");
				}
				if (false == normalNoElement) {
					if (NULL == elementParser) {
						SVG_ERROR("(l "<<child->Row()<<") error on node: \""<<localValue<<"\" allocation error or not supported ...");
					} else {
						if (false == elementParser->Parse(child, m_transformMatrix, size)) {
							SVG_ERROR("(l "<<child->Row()<<") error on node: \""<<localValue<<"\" Sub Parsing ERROR");
							delete(elementParser);
							elementParser = NULL;
						} else {
							if (maxSize.x<size.x) {
								maxSize.x=size.x;
							}
							if (maxSize.y<size.y) {
								maxSize.y=size.y;
							}
							// add element in the system
							m_subElementList.PushBack(elementParser);
						}
					}
				}
			}
		}
		if (m_size.x==0 || m_size.y==0) {
			m_size.x=(int32_t)maxSize.x;
			m_size.y=(int32_t)maxSize.y;
		} else {
			m_size.x=(int32_t)m_size.x;
			m_size.y=(int32_t)m_size.y;
		}
	}
	if (NULL != fileBuffer) {
		delete[] fileBuffer;
	}
	//DisplayDebug();
}

svg::Parser::~Parser(void)
{
	if(NULL != m_renderedElement) {
		delete(m_renderedElement);
		m_renderedElement = NULL;
	}
}



void svg::Parser::DisplayDebug(void)
{
	SVG_DEBUG("Main SVG node : size=" << m_size);
	for (int32_t iii=0; iii<m_subElementList.Size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->Display(1);
		}
	}
}


void svg::Parser::AggDraw(svg::Renderer& myRenderer, agg::trans_affine& basicTrans)
{
	for (int32_t iii=0; iii<m_subElementList.Size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->AggDraw(myRenderer, basicTrans);
		}
	}
}


void svg::Parser::GenerateTestFile(void)
{
	int32_t SizeX = m_size.x;
	if (SizeX == 0) {
		SizeX = 64;
	}
	int32_t SizeY = m_size.y;
	if (SizeY == 0) {
		SizeY = 64;
	}
	if(NULL != m_renderedElement) {
		delete(m_renderedElement);
		m_renderedElement = NULL;
	}
	m_renderedElement = new svg::Renderer(SizeX, SizeY);
	// create the first element matrix modification ...
	agg::trans_affine basicTrans;
	//basicTrans *= agg::trans_affine_translation(-g_base_dx, -g_base_dy);
	//basicTrans *= agg::trans_affine_scaling(2, 2);
	//basicTrans *= agg::trans_affine_rotation(g_angle);// + agg::pi);
	//basicTrans *= agg::trans_affine_skewing(2.0, 5.0);
	//basicTrans *= agg::trans_affine_translation(width*0.3, height/2);
	//basicTrans *= agg::trans_affine_translation(width/3, height/3);
	
	
	AggDraw(*m_renderedElement, basicTrans);
	etk::UString tmpFileOut = "yyy_out_";
	tmpFileOut += m_fileName.GetNameFile();
	tmpFileOut += ".ppm";
	m_renderedElement->WritePpm(tmpFileOut);
	
}



void svg::Parser::GenerateAnImage(int32_t sizeX, int32_t sizeY)
{
	int32_t SizeX = sizeX;
	if (SizeX == 0) {
		SVG_ERROR("SizeX == 0 ==> set 64");
		SizeX = 64;
	}
	int32_t SizeY = sizeY;
	if (SizeY == 0) {
		SVG_ERROR("SizeY == 0 ==> set 64");
		SizeY = 64;
	}
	SVG_INFO("Generate size (" << SizeX << "," << SizeY << ")");
	if(NULL != m_renderedElement) {
		delete(m_renderedElement);
		m_renderedElement = NULL;
	}
	
	m_renderedElement = new svg::Renderer(SizeX, SizeY);
	// create the first element matrix modification ...
	agg::trans_affine basicTrans;
	//basicTrans *= agg::trans_affine_translation(-g_base_dx, -g_base_dy);
	basicTrans *= agg::trans_affine_scaling(SizeX/m_size.x, SizeY/m_size.y);
	//basicTrans *= agg::trans_affine_rotation(g_angle);// + agg::pi);
	//basicTrans *= agg::trans_affine_skewing(2.0, 5.0);
	//basicTrans *= agg::trans_affine_translation(width*0.3, height/2);
	//basicTrans *= agg::trans_affine_translation(width/3, height/3);
	
	AggDraw(*m_renderedElement, basicTrans);
	/*
	etk::UString tmpFileOut = "zzz_out_test.ppm";
	m_renderedElement->WritePpm(tmpFileOut);
	*/
}

void svg::Parser::GenerateAnImage(etk::Vector2D<int32_t> size, draw::Image& output)
{
	GenerateAnImage(size.x, size.y);
	output.Resize(size);
	draw::Color tmpp(0,0,0,0);
	output.SetFillColor(tmpp);
	output.Clear();
	if(NULL != m_renderedElement) {
		uint8_t* pointerOnData = m_renderedElement->GetDataPointer();
		int32_t  sizeData = m_renderedElement->GetDataSize();
		uint8_t* tmpOut = (uint8_t*)output.GetTextureDataPointer();
		memcpy(tmpOut, pointerOnData, sizeData);
	}
}

uint8_t* svg::Parser::GetPointerOnData(void)
{
	if(NULL == m_renderedElement) {
		return NULL;
	}
	return m_renderedElement->GetDataPointer();
}

uint32_t svg::Parser::GetSizeOnData(void)
{
	if(NULL == m_renderedElement) {
		return 0;
	}
	return m_renderedElement->GetDataSize();
}




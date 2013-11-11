/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/esvg.h>
#include <esvg/Base.h>
#include <esvg/Circle.h>
#include <esvg/Ellipse.h>
#include <esvg/Line.h>
#include <esvg/Path.h>
#include <esvg/Polygon.h>
#include <esvg/Polyline.h>
#include <esvg/Rectangle.h>
#include <esvg/Text.h>
#include <esvg/Group.h>

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


#undef __class__
#define __class__ "Document"


esvg::Document::Document(const std::string& _fileName) : m_renderedElement(NULL) {
	m_fileName = _fileName;
	m_version = "0.0";
	m_loadOK = true;
	m_paint.fill = (int32_t)0xFF0000FF;
	m_paint.stroke = (int32_t)0xFFFFFF00;
	
	m_paint.strokeWidth = 1.0;
	m_paint.viewPort.setValue(255,255);
	m_paint.flagEvenOdd = false;
	m_paint.lineJoin = esvg::lineJoinMiter;
	m_paint.lineCap = esvg::lineCapButt;
	m_size.setValue(0,0);
	
	exml::Document doc;
	if (false == doc.load(m_fileName)) {
		SVG_ERROR("Error occured when loading XML : " << m_fileName);
		m_loadOK = false;
		return;
	}
	
	if (0 == doc.size() ) {
		SVG_ERROR("(l ?) No nodes in the xml file ... \"" << m_fileName << "\"");
		m_loadOK = false;
		return;
	}
	
	exml::Element* root = (exml::Element*)doc.getNamed( "svg" );
	if (NULL == root ) {
		SVG_ERROR("(l ?) main node not find: \"svg\" in \"" << m_fileName << "\"");
		m_loadOK = false;
		return;
	}
	// get the svg version :
	m_version = root->getAttribute("version");
	// parse ...
	vec2 pos(0,0);
	parseTransform(root);
	parsePosition(root, pos, m_size);
	parsePaintAttr(root);
	SVG_VERBOSE("parsed .ROOT trans : (" << m_transformMatrix.sx << "," << m_transformMatrix.shy << "," << m_transformMatrix.shx << "," << m_transformMatrix.sy << "," << m_transformMatrix.tx << "," << m_transformMatrix.ty << ")");
	vec2 maxSize(0,0);
	vec2 size(0,0);
	// parse all sub node :
	for(int32_t iii=0; iii< root->size(); iii++) {
		exml::Element* child = root->getElement(iii);
		if (child == NULL) {
			// comment trsh here...
			continue;
		}
		esvg::Base *elementParser = NULL;
		if (child->getValue() == "g") {
			elementParser = new esvg::Group(m_paint);
		} else if (child->getValue() == "a") {
			SVG_INFO("Note : 'a' balise is parsed like a g balise ...");
			elementParser = new esvg::Group(m_paint);
		} else if (child->getValue() == "title") {
			m_title = "TODO : set the title here ...";
			continue;
		} else if (child->getValue() == "path") {
			elementParser = new esvg::Path(m_paint);
		} else if (child->getValue() == "rect") {
			elementParser = new esvg::Rectangle(m_paint);
		} else if (child->getValue() == "circle") {
			elementParser = new esvg::Circle(m_paint);
		} else if (child->getValue() == "ellipse") {
			elementParser = new esvg::Ellipse(m_paint);
		} else if (child->getValue() == "line") {
			elementParser = new esvg::Line(m_paint);
		} else if (child->getValue() == "polyline") {
			elementParser = new esvg::Polyline(m_paint);
		} else if (child->getValue() == "polygon") {
			elementParser = new esvg::Polygon(m_paint);
		} else if (child->getValue() == "text") {
			elementParser = new esvg::Text(m_paint);
		} else if (child->getValue() == "defs") {
			// Node ignore : must implement it later ...
			continue;
		} else if (child->getValue() == "sodipodi:namedview") {
			// Node ignore : generaly inkscape data
			continue;
		} else if (child->getValue() == "metadata") {
			// Node ignore : generaly inkscape data
			continue;
		} else {
			SVG_ERROR("(l "<<child->getPos()<<") node not suported : \""<<child->getValue()<<"\" must be [title,g,a,path,rect,circle,ellipse,line,polyline,polygon,text,metadata]");
		}
		if (NULL == elementParser) {
			SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" allocation error or not supported ...");
			continue;
		}
		if (false == elementParser->parse(child, m_transformMatrix, size)) {
			SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" Sub Parsing ERROR");
			delete(elementParser);
			elementParser = NULL;
			continue;
		}
		if (maxSize.x()<size.x()) {
			maxSize.setX(size.x());
		}
		if (maxSize.y()<size.y()) {
			maxSize.setY(size.y());
		}
		// add element in the system
		m_subElementList.push_back(elementParser);
	}
	if (m_size.x() == 0 || m_size.y()==0) {
		m_size.setValue((int32_t)maxSize.x(), (int32_t)maxSize.y());
	} else {
		m_size.setValue((int32_t)m_size.x(), (int32_t)m_size.y());
	}
	//DisplayDebug();
}

esvg::Document::~Document(void) {
	if(NULL != m_renderedElement) {
		delete(m_renderedElement);
		m_renderedElement = NULL;
	}
}



void esvg::Document::displayDebug(void) {
	SVG_DEBUG("Main SVG node : size=" << m_size);
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->display(1);
		}
	}
}


void esvg::Document::aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans)
{
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (NULL != m_subElementList[iii]) {
			m_subElementList[iii]->aggDraw(_myRenderer, _basicTrans);
		}
	}
}


void esvg::Document::generateTestFile(void)
{
	int32_t sizeX = m_size.x();
	if (sizeX == 0) {
		sizeX = 64;
	}
	int32_t sizeY = m_size.y();
	if (sizeY == 0) {
		sizeY = 64;
	}
	if(NULL != m_renderedElement) {
		delete(m_renderedElement);
		m_renderedElement = NULL;
	}
	m_renderedElement = new esvg::Renderer(sizeX, sizeY);
	// create the first element matrix modification ...
	agg::trans_affine basicTrans;
	//basicTrans *= agg::trans_affine_translation(-g_base_dx, -g_base_dy);
	//basicTrans *= agg::trans_affine_scaling(2, 2);
	//basicTrans *= agg::trans_affine_rotation(g_angle);// + agg::pi);
	//basicTrans *= agg::trans_affine_skewing(2.0, 5.0);
	//basicTrans *= agg::trans_affine_translation(width*0.3, height/2);
	//basicTrans *= agg::trans_affine_translation(width/3, height/3);
	
	
	aggDraw(*m_renderedElement, basicTrans);
	std::string tmpFileOut = "yyy_out_";
	tmpFileOut += m_fileName;
	tmpFileOut += ".ppm";
	m_renderedElement->writePpm(tmpFileOut);
	
}



void esvg::Document::generateAnImage(int32_t _sizeX, int32_t _sizeY)
{
	int32_t sizeX = _sizeX;
	if (sizeX == 0) {
		SVG_ERROR("SizeX == 0 ==> set 64");
		sizeX = 64;
	}
	int32_t sizeY = _sizeY;
	if (sizeY == 0) {
		SVG_ERROR("SizeY == 0 ==> set 64");
		sizeY = 64;
	}
	SVG_INFO("Generate size (" << sizeX << "," << sizeY << ")");
	if(NULL != m_renderedElement) {
		delete(m_renderedElement);
		m_renderedElement = NULL;
	}
	
	m_renderedElement = new esvg::Renderer(sizeX, sizeY);
	// create the first element matrix modification ...
	agg::trans_affine basicTrans;
	//basicTrans *= agg::trans_affine_translation(-g_base_dx, -g_base_dy);
	basicTrans *= agg::trans_affine_scaling(sizeX/m_size.x(), sizeY/m_size.y());
	//basicTrans *= agg::trans_affine_rotation(g_angle);// + agg::pi);
	//basicTrans *= agg::trans_affine_skewing(2.0, 5.0);
	//basicTrans *= agg::trans_affine_translation(width*0.3, height/2);
	//basicTrans *= agg::trans_affine_translation(width/3, height/3);
	
	aggDraw(*m_renderedElement, basicTrans);
	/*
	std::string tmpFileOut = "zzz_out_test.ppm";
	m_renderedElement->WritePpm(tmpFileOut);
	*/
}

void esvg::Document::generateAnImage(draw::Image& _output)
{
	generateAnImage(ivec2(m_size.x(),m_size.y()), _output);
}

void esvg::Document::generateAnImage(ivec2 _size, draw::Image& _output)
{
	generateAnImage(_size.x(), _size.y());
	_output.resize(_size);
	draw::Color tmpp(0,0,0,0);
	_output.setFillColor(tmpp);
	_output.clear();
	if(NULL != m_renderedElement) {
		uint8_t* pointerOnData = m_renderedElement->getDataPointer();
		int32_t  sizeData = m_renderedElement->getDataSize();
		uint8_t* tmpOut = (uint8_t*)_output.getTextureDataPointer();
		memcpy(tmpOut, pointerOnData, sizeData);
	}
}

uint8_t* esvg::Document::getPointerOnData(void)
{
	if(NULL == m_renderedElement) {
		return NULL;
	}
	return m_renderedElement->getDataPointer();
}

uint32_t esvg::Document::getSizeOnData(void)
{
	if(NULL == m_renderedElement) {
		return 0;
	}
	return m_renderedElement->getDataSize();
}




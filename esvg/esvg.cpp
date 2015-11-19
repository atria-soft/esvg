/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
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

#undef __class__
#define __class__ "Document"


esvg::Document::Document() :
  m_renderedElement(nullptr) {
	m_fileName = "";
	m_version = "0.0";
	m_loadOK = false;
	m_paint.fill = etk::color::none;
	m_paint.stroke = etk::color::none;
	
	m_paint.strokeWidth = 1.0;
	m_paint.viewPort.setValue(255,255);
	m_paint.flagEvenOdd = false;
	m_paint.lineJoin = esvg::join_miter;
	m_paint.lineCap = esvg::cap_butt;
	m_size.setValue(0,0);
}

esvg::Document::~Document() {
	delete(m_renderedElement);
	m_renderedElement = nullptr;
}



void esvg::Document::displayDebug() {
	SVG_DEBUG("Main SVG node : size=" << m_size);
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (m_subElementList[iii] != nullptr) {
			m_subElementList[iii]->display(1);
		}
	}
}


void esvg::Document::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans)
{
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (m_subElementList[iii] != nullptr) {
			m_subElementList[iii]->draw(_myRenderer, _basicTrans);
		}
	}
}


void esvg::Document::generateTestFile()
{
	int32_t sizeX = m_size.x();
	if (sizeX == 0) {
		sizeX = 64;
	}
	int32_t sizeY = m_size.y();
	if (sizeY == 0) {
		sizeY = 64;
	}
	delete(m_renderedElement);
	m_renderedElement = nullptr;
	m_renderedElement = new esvg::Renderer(ivec2(sizeX, sizeY));
	// create the first element matrix modification ...
	mat2 basicTrans;
	//basicTrans *= etk::mat2Translate(vec2(-g_base_dx, -g_base_dy));
	//basicTrans *= etk::mat2Scale(vec2(2, 2));
	//basicTrans *= etk::mat2Rotate(vec2(g_angle));
	//basicTrans *= etk::mat2Skew(vec2(2.0, 5.0));
	//basicTrans *= etk::mat2Translate(vec2(width*0.3, height/2));
	//basicTrans *= etk::mat2Translate(vec2(width/3, height/3));
	
	
	draw(*m_renderedElement, basicTrans);
	std::string tmpFileOut = "yyy_out_";
	tmpFileOut += m_fileName;
	tmpFileOut += ".ppm";
	m_renderedElement->writePpm(tmpFileOut);
	
}


// FOR TEST only ...
void esvg::Document::generateAnImage(const ivec2& _size, const std::string& _fileName) {
	int32_t sizeX = _size.x();
	if (sizeX == 0) {
		SVG_ERROR("SizeX == 0 ==> set 64");
		sizeX = 64;
	}
	int32_t sizeY = _size.y();
	if (sizeY == 0) {
		SVG_ERROR("SizeY == 0 ==> set 64");
		sizeY = 64;
	}
	SVG_INFO("Generate size (" << sizeX << "," << sizeY << ")");
	delete(m_renderedElement);
	m_renderedElement = nullptr;
	
	m_renderedElement = new esvg::Renderer(ivec2(sizeX, sizeY));
	// create the first element matrix modification ...
	mat2 basicTrans;
	//basicTrans *= etk::mat2Translate(vec2(-g_base_dx, -g_base_dy));
	basicTrans *= etk::mat2Scale(vec2(sizeX/m_size.x(), sizeY/m_size.y()));
	//basicTrans *= etk::mat2Rotate(g_angle);// + agg::pi);
	//basicTrans *= etk::mat2Skew(vec2(2.0, 5.0));
	//basicTrans *= etk::mat2Translate(vec2(width*0.3, height/2));
	//basicTrans *= etk::mat2Translate(vec2(width/3, height/3));
	
	draw(*m_renderedElement, basicTrans);
	m_renderedElement->writePpm(_fileName);
}
/*
void esvg::Document::generateAnImage(draw::Image& _output) {
	generateAnImage(ivec2(m_size.x(),m_size.y()), _output);
}

void esvg::Document::generateAnImage(ivec2 _size, draw::Image& _output) {
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
*/
uint8_t* esvg::Document::getPointerOnData() {
	if(m_renderedElement == nullptr) {
		return nullptr;
	}
	return m_renderedElement->getDataPointer();
}

uint32_t esvg::Document::getSizeOnData() {
	if(m_renderedElement == nullptr) {
		return 0;
	}
	return m_renderedElement->getDataSize();
}

void esvg::Document::clear() {
	m_fileName = "";
	m_version = "0.0";
	m_loadOK = true;
	m_paint.fill = etk::color::none;
	m_paint.stroke = etk::color::none;
	
	m_paint.strokeWidth = 1.0;
	m_paint.viewPort.setValue(255,255);
	m_paint.flagEvenOdd = false;
	m_paint.lineJoin = esvg::join_miter;
	m_paint.lineCap = esvg::cap_butt;
	m_size.setValue(0,0);
}


bool esvg::Document::parse(const std::string& _data) {
	clear();
	exml::Document doc;
	if (doc.parse(_data) == false) {
		SVG_ERROR("Error occured when loading SVG : " << m_fileName);
		m_loadOK = false;
		return m_loadOK;
	}
	if (doc.size() == 0) {
		SVG_ERROR("(l ?) No nodes in the SVG file ... \"" << m_fileName << "\"");
		m_loadOK = false;
		return m_loadOK;
	}
	std::shared_ptr<exml::Element> root = doc.getNamed("svg" );
	if (root == nullptr) {
		SVG_ERROR("(l ?) main node not find: \"svg\" in \"" << m_fileName << "\"");
		m_loadOK = false;
		return m_loadOK;
	}
	m_loadOK = parseXMLData(root);
	return m_loadOK;
}

bool esvg::Document::generate(std::string& _data) {
	return false;
}

bool esvg::Document::load(const std::string& _file) {
	clear();
	m_fileName = _file;
	exml::Document doc;
	if (doc.load(m_fileName) == false) {
		SVG_ERROR("Error occured when loading SVG : " << m_fileName);
		m_loadOK = false;
		return m_loadOK;
	}
	if (doc.size() == 0) {
		SVG_ERROR("(l ?) No nodes in the SVG file ... \"" << m_fileName << "\"");
		m_loadOK = false;
		return m_loadOK;
	}
	std::shared_ptr<exml::Element> root = doc.getNamed("svg" );
	if (root == nullptr) {
		SVG_ERROR("(l ?) main node not find: \"svg\" in \"" << m_fileName << "\"");
		m_loadOK = false;
		return m_loadOK;
	}
	m_loadOK = parseXMLData(root);
	return m_loadOK;
}

bool esvg::Document::store(const std::string& _file) {
	return false;
}



bool esvg::Document::parseXMLData(const std::shared_ptr<exml::Element>& _root) {
	// get the svg version :
	m_version = _root->getAttribute("version");
	// parse ...
	vec2 pos(0,0);
	parseTransform(_root);
	parsePosition(_root, pos, m_size);
	parsePaintAttr(_root);
	SVG_VERBOSE("parsed .ROOT trans: " << m_transformMatrix);
	vec2 maxSize(0,0);
	vec2 size(0,0);
	// parse all sub node :
	for(int32_t iii=0; iii< _root->size(); iii++) {
		std::shared_ptr<exml::Element> child = _root->getElement(iii);
		if (child == nullptr) {
			// comment trsh here...
			continue;
		}
		esvg::Base *elementParser = nullptr;
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
		if (elementParser == nullptr) {
			SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" allocation error or not supported ...");
			continue;
		}
		if (elementParser->parse(child, m_transformMatrix, size) == false) {
			SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" Sub Parsing ERROR");
			delete(elementParser);
			elementParser = nullptr;
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
	displayDebug();
	return true;
}



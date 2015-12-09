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
#include <esvg/LinearGradient.h>
#include <esvg/RadialGradient.h>

#undef __class__
#define __class__ "Document"


esvg::Document::Document() {
	m_fileName = "";
	m_version = "0.0";
	m_loadOK = false;
	m_size.setValue(0,0);
}

esvg::Document::~Document() {
	
}



void esvg::Document::displayDebug() {
	SVG_DEBUG("Main SVG: size=" << m_size);
	SVG_DEBUG("    refs:");
	for (int32_t iii=0; iii<m_refList.size(); iii++) {
		if (m_refList[iii] != nullptr) {
			m_refList[iii]->display(2);
		}
	}
	SVG_DEBUG("    Nodes:");
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (m_subElementList[iii] != nullptr) {
			m_subElementList[iii]->display(2);
		}
	}
}


void esvg::Document::draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level) {
	for (int32_t iii=0; iii<m_subElementList.size(); iii++) {
		if (m_subElementList[iii] != nullptr) {
			m_subElementList[iii]->draw(_myRenderer, _basicTrans);
		}
	}
}

// FOR TEST only ...
void esvg::Document::generateAnImage(const ivec2& _size, const std::string& _fileName, bool _visualDebug) {
	ivec2 sizeRender = _size;
	if (sizeRender.x() <= 0) {
		sizeRender.setX(m_size.x());
	}
	if (sizeRender.y() <= 0) {
		sizeRender.setY(m_size.y());
	}
	SVG_DEBUG("Generate size " << sizeRender);
	
	std::shared_ptr<esvg::Renderer> renderedElement = std::make_shared<esvg::Renderer>(sizeRender, this, _visualDebug);
	// create the first element matrix modification ...
	mat2 basicTrans;
	basicTrans *= etk::mat2Scale(vec2(sizeRender.x()/m_size.x(), sizeRender.y()/m_size.y()));
	
	draw(*renderedElement, basicTrans);
	
	if (etk::end_with(_fileName, ".ppm") == true) {
		renderedElement->writePPM(_fileName);
	} else if (etk::end_with(_fileName, ".bmp") == true) {
		renderedElement->writeBMP(_fileName);
	} else {
		SVG_ERROR("Can not store with this extention : " << _fileName << " not in .bmp/.ppm");
	}
}


std::vector<etk::Color<float,4>> esvg::Document::renderImageFloatRGBA(ivec2& _size) {
	if (_size.x() <= 0) {
		_size.setX(m_size.x());
	}
	if (_size.y() <= 0) {
		_size.setY(m_size.y());
	}
	SVG_DEBUG("Generate size " << _size);
	std::shared_ptr<esvg::Renderer> renderedElement = std::make_shared<esvg::Renderer>(_size, this);
	// create the first element matrix modification ...
	mat2 basicTrans;
	basicTrans *= etk::mat2Scale(vec2(_size.x()/m_size.x(), _size.y()/m_size.y()));
	draw(*renderedElement, basicTrans);
	
	// direct return the generated data ...
	return renderedElement->getData();
}

std::vector<etk::Color<float,3>> esvg::Document::renderImageFloatRGB(ivec2& _size) {
	std::vector<etk::Color<float,4>> data = renderImageFloatRGBA(_size);
	// Reduce scope:
	std::vector<etk::Color<float,3>> out;
	out.resize(data.size());
	for (size_t iii=0; iii<data.size(); ++iii) {
		out[iii] = data[iii];
	}
	return out;
}

std::vector<etk::Color<uint8_t,4>> esvg::Document::renderImageU8RGBA(ivec2& _size) {
	std::vector<etk::Color<float,4>> data = renderImageFloatRGBA(_size);
	// Reduce scope:
	std::vector<etk::Color<uint8_t,4>> out;
	out.resize(data.size());
	for (size_t iii=0; iii<data.size(); ++iii) {
		out[iii] = data[iii];
	}
	return out;
}

std::vector<etk::Color<uint8_t,3>> esvg::Document::renderImageU8RGB(ivec2& _size) {
	std::vector<etk::Color<float,4>> data = renderImageFloatRGBA(_size);
	// Reduce scope:
	std::vector<etk::Color<uint8_t,3>> out;
	out.resize(data.size());
	for (size_t iii=0; iii<data.size(); ++iii) {
		out[iii] = data[iii];
	}
	return out;
}

void esvg::Document::clear() {
	m_fileName = "";
	m_version = "0.0";
	m_loadOK = true;
	m_paint.clear();
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
	cleanStyleProperty(root);
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
	std::shared_ptr<exml::Element> root = doc.getNamed("svg");
	if (root == nullptr) {
		SVG_ERROR("(l ?) main node not find: \"svg\" in \"" << m_fileName << "\"");
		m_loadOK = false;
		return m_loadOK;
	}
	cleanStyleProperty(root);
	m_loadOK = parseXMLData(root);
	return m_loadOK;
}

bool esvg::Document::store(const std::string& _file) {
	return false;
}

bool esvg::Document::cleanStyleProperty(const std::shared_ptr<exml::Element>& _root) {
	// for each nodes:
	for(int32_t iii=0; iii< _root->size(); iii++) {
		std::shared_ptr<exml::Element> child = _root->getElement(iii);
		if (child == nullptr) {
			continue;
		}
		// get attribute style:
		if (child->existAttribute("style") == true) {
			std::string content = child->getAttribute("style");
			if (content.size() != 0) {
				std::vector<std::string> listStyle = etk::split(content, ';');
				for (auto &it : listStyle) {
					std::vector<std::string> value = etk::split(it, ':');
					if (value.size() != 2) {
						SVG_ERROR("parsing style with a wrong patern : " << it << " missing ':'");
						continue;
					}
					// TODO : Check if the attibute already exist ...
					child->setAttribute(value[0], value[1]);
				}
			}
			// remove attribute style:
			child->removeAttribute("style");
		}
		// sub-parsing ...
		cleanStyleProperty(child);
	}
	return true;
}

bool esvg::Document::parseXMLData(const std::shared_ptr<exml::Element>& _root, bool _isReference) {
	// get the svg version :
	m_version = _root->getAttribute("version");
	// parse ...
	vec2 pos(0,0);
	if (_isReference == false) {
		parseTransform(_root);
		parsePosition(_root, pos, m_size);
		parsePaintAttr(_root);
		SVG_VERBOSE("parsed .ROOT trans: " << m_transformMatrix);
	} else {
		SVG_VERBOSE("Parse Reference section ... (no attibute)");
	}
	vec2 maxSize(0,0);
	vec2 size(0,0);
	// parse all sub node:
	for(int32_t iii=0; iii< _root->size(); iii++) {
		std::shared_ptr<exml::Element> child = _root->getElement(iii);
		if (child == nullptr) {
			// comment can be here...
			continue;
		}
		std::shared_ptr<esvg::Base> elementParser;
		if (child->getValue() == "g") {
			elementParser = std::make_shared<esvg::Group>(m_paint);
		} else if (child->getValue() == "a") {
			SVG_INFO("Note : 'a' balise is parsed like a g balise ...");
			elementParser = std::make_shared<esvg::Group>(m_paint);
		} else if (child->getValue() == "title") {
			m_title = "TODO : set the title here ...";
			continue;
		} else if (child->getValue() == "path") {
			elementParser = std::make_shared<esvg::Path>(m_paint);
		} else if (child->getValue() == "rect") {
			elementParser = std::make_shared<esvg::Rectangle>(m_paint);
		} else if (child->getValue() == "circle") {
			elementParser = std::make_shared<esvg::Circle>(m_paint);
		} else if (child->getValue() == "ellipse") {
			elementParser = std::make_shared<esvg::Ellipse>(m_paint);
		} else if (child->getValue() == "line") {
			elementParser = std::make_shared<esvg::Line>(m_paint);
		} else if (child->getValue() == "polyline") {
			elementParser = std::make_shared<esvg::Polyline>(m_paint);
		} else if (child->getValue() == "polygon") {
			elementParser = std::make_shared<esvg::Polygon>(m_paint);
		} else if (child->getValue() == "text") {
			elementParser = std::make_shared<esvg::Text>(m_paint);
		} else if (child->getValue() == "radialGradient") {
			if (_isReference == false) {
				SVG_ERROR("'" << child->getValue() << "' node must not be defined outside a defs Section");
				continue;
			} else {
				//elementParser = std::make_shared<esvg::RadialGradient>(m_paint);
			}
		} else if (child->getValue() == "linearGradient") {
			if (_isReference == false) {
				SVG_ERROR("'" << child->getValue() << "' node must not be defined outside a defs Section");
				continue;
			} else {
				elementParser = std::make_shared<esvg::LinearGradient>(m_paint);
			}
		} else if (child->getValue() == "defs") {
			if (_isReference == true) {
				SVG_ERROR("'" << child->getValue() << "' node must not be defined in a defs Section");
				continue;
			} else {
				bool retRefs = parseXMLData(child, true);
				// TODO : Use retRefs ...
				continue;
			}
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
		if (elementParser->parseXML(child, m_transformMatrix, size) == false) {
			SVG_ERROR("(l "<<child->getPos()<<") error on node: \""<<child->getValue()<<"\" Sub Parsing ERROR");
			elementParser.reset();
			continue;
		}
		if (maxSize.x()<size.x()) {
			maxSize.setX(size.x());
		}
		if (maxSize.y()<size.y()) {
			maxSize.setY(size.y());
		}
		// add element in the system
		if (_isReference == false) {
			m_subElementList.push_back(elementParser);
		} else {
			m_refList.push_back(elementParser);
		}
	}
	if (m_size.x() == 0 || m_size.y()==0) {
		m_size.setValue((int32_t)maxSize.x(), (int32_t)maxSize.y());
	} else {
		m_size.setValue((int32_t)m_size.x(), (int32_t)m_size.y());
	}
	if (_isReference == false) {
		displayDebug();
	}
	return true;
}



std::shared_ptr<esvg::Base> esvg::Document::getReference(const std::string& _name) {
	if (_name == "") {
		SVG_ERROR("request a reference with no name ... ");
		return nullptr;
	}
	for (auto &it : m_refList) {
		if (it == nullptr) {
			continue;
		}
		if (it->getId() == _name) {
			return it;
		}
	}
	SVG_ERROR("Can not find reference name : '" << _name << "'");
	return nullptr;
}



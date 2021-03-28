/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/esvg.hpp>
#include <esvg/Base.hpp>
#include <esvg/Circle.hpp>
#include <esvg/Ellipse.hpp>
#include <esvg/Line.hpp>
#include <esvg/Path.hpp>
#include <esvg/Polygon.hpp>
#include <esvg/Polyline.hpp>
#include <esvg/Rectangle.hpp>
#include <esvg/Text.hpp>
#include <esvg/Group.hpp>
#include <esvg/LinearGradient.hpp>
#include <esvg/RadialGradient.hpp>

esvg::Document::Document() {
	this.uri = "";
	this.version = "0.0";
	this.loadOK = false;
	this.size.setValue(0,0);
}

esvg::Document::~Document() {
	
}



void esvg::Document::displayDebug() {
	Log.debug("Main SVG: size=" << this.size);
	Log.debug("    refs:");
	for (size_t iii=0; iii<this.refList.size(); iii++) {
		if (this.refList[iii] != null) {
			this.refList[iii]->display(2);
		}
	}
	Log.debug("    Nodes:");
	for (size_t iii=0; iii<this.subElementList.size(); iii++) {
		if (this.subElementList[iii] != null) {
			this.subElementList[iii]->display(2);
		}
	}
}


void esvg::Document::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	for (size_t iii=0; iii<this.subElementList.size(); iii++) {
		if (this.subElementList[iii] != null) {
			this.subElementList[iii]->draw(_myRenderer, _basicTrans);
		}
	}
}

// FOR TEST only ...
void esvg::Document::generateAnImage(const etk::Uri& _uri, boolean _visualDebug) {
	generateAnImage(this.size, _uri, _visualDebug);
}
void esvg::Document::generateAnImage(const Vector2i& _size, const etk::Uri& _uri, boolean _visualDebug) {
	Vector2i sizeRender = _size;
	if (sizeRender.x() <= 0) {
		sizeRender.setX(this.size.x());
	}
	if (sizeRender.y() <= 0) {
		sizeRender.setY(this.size.y());
	}
	Log.debug("Generate size " << sizeRender);
	
	ememory::SharedPtr<esvg::Renderer> renderedElement = ememory::makeShared<esvg::Renderer>(sizeRender, this, _visualDebug);
	// create the first element matrix modification ...
	mat2x3 basicTrans;
	basicTrans *= etk::mat2x3Scale(Vector2f(sizeRender.x()/this.size.x(), sizeRender.y()/this.size.y()));
	
	draw(*renderedElement, basicTrans);
	
	if (_uri.getPath().getExtention() == "ppm") {
		renderedElement->writePPM(_uri);
	} else if (_uri.getPath().getExtention() == "bmp") {
		renderedElement->writeBMP(_uri);
	} else {
		Log.error("Can not store with this extention : " << _uri << " not in .bmp/.ppm");
	}
}


List<etk::Color<float,4>> esvg::Document::renderImageFloatRGBA(Vector2i& _size) {
	if (_size.x() <= 0) {
		_size.setX(this.size.x());
	}
	if (_size.y() <= 0) {
		_size.setY(this.size.y());
	}
	Log.debug("Generate size " << _size);
	ememory::SharedPtr<esvg::Renderer> renderedElement = ememory::makeShared<esvg::Renderer>(_size, this);
	// create the first element matrix modification ...
	mat2x3 basicTrans;
	basicTrans *= etk::mat2x3Scale(Vector2f(_size.x()/this.size.x(), _size.y()/this.size.y()));
	draw(*renderedElement, basicTrans);
	
	// direct return the generated data ...
	return renderedElement->getData();
}

List<etk::Color<float,3>> esvg::Document::renderImageFloatRGB(Vector2i& _size) {
	List<etk::Color<float,4>> data = renderImageFloatRGBA(_size);
	// Reduce scope:
	List<etk::Color<float,3>> out;
	out.resize(data.size());
	for (size_t iii=0; iii<data.size(); ++iii) {
		out[iii] = data[iii];
	}
	return out;
}

List<etk::Color<uint8_t,4>> esvg::Document::renderImageU8RGBA(Vector2i& _size) {
	List<etk::Color<float,4>> data = renderImageFloatRGBA(_size);
	// Reduce scope:
	List<etk::Color<uint8_t,4>> out;
	out.resize(data.size());
	for (size_t iii=0; iii<data.size(); ++iii) {
		out[iii] = data[iii];
	}
	return out;
}

List<etk::Color<uint8_t,3>> esvg::Document::renderImageU8RGB(Vector2i& _size) {
	List<etk::Color<float,4>> data = renderImageFloatRGBA(_size);
	// Reduce scope:
	List<etk::Color<uint8_t,3>> out;
	out.resize(data.size());
	for (size_t iii=0; iii<data.size(); ++iii) {
		out[iii] = data[iii];
	}
	return out;
}

void esvg::Document::clear() {
	this.uri = "";
	this.version = "0.0";
	this.loadOK = true;
	this.paint.clear();
	this.size.setValue(0,0);
}


boolean esvg::Document::parse(const etk::String& _data) {
	clear();
	exml::Document doc;
	if (doc.parse(_data) == false) {
		Log.error("Error occured when loading SVG: " << this.uri);
		this.loadOK = false;
		return this.loadOK;
	}
	if (doc.nodes.size() == 0) {
		Log.error("(l ?) No nodes in the SVG file ... '" << this.uri << "'");
		this.loadOK = false;
		return this.loadOK;
	}
	exml::Element root = doc.nodes["svg"];
	if (root.exist() == false) {
		Log.error("(l ?) main node not find: 'svg' in '" << this.uri << "'");
		this.loadOK = false;
		return this.loadOK;
	}
	cleanStyleProperty(root);
	this.loadOK = parseXMLData(root);
	return this.loadOK;
}

boolean esvg::Document::generate(etk::String& _data) {
	return false;
}

boolean esvg::Document::load(const etk::Uri& _uri) {
	clear();
	this.uri = _uri;
	exml::Document doc;
	if (doc.load(this.uri) == false) {
		Log.error("Error occured when loading SVG : " << this.uri);
		this.loadOK = false;
		return this.loadOK;
	}
	if (doc.nodes.size() == 0) {
		Log.error("(l ?) No nodes in the SVG file ... '" << this.uri << "'");
		this.loadOK = false;
		return this.loadOK;
	}
	exml::Element root = doc.nodes["svg"];
	if (root.exist() == false) {
		Log.error("(l ?) main node not find: 'svg' in '" << this.uri << "'");
		this.loadOK = false;
		return this.loadOK;
	}
	cleanStyleProperty(root);
	this.loadOK = parseXMLData(root);
	return this.loadOK;
}

boolean esvg::Document::store(const etk::Uri& _uri) {
	Log.todo("not implemented store in SVG...");
	return false;
}

boolean esvg::Document::cleanStyleProperty(const exml::Element& _root) {
	// for each nodes:
	for(auto it: _root.nodes) {
		exml::Element child = it.toElement();
		if (child.exist() == false) {
			continue;
		}
		// get attribute style:
		if (child.attributes.exist("style") == true) {
			etk::String content = child.attributes["style"];
			if (content.size() != 0) {
				List<etk::String> listStyle = etk::split(content, ';');
				for (auto &it : listStyle) {
					List<etk::String> value = etk::split(it, ':');
					if (value.size() != 2) {
						Log.error("parsing style with a wrong patern : " << it << " missing ':'");
						continue;
					}
					// TODO : Check if the attibute already exist ...
					child.attributes.set(value[0], value[1]);
				}
			}
			// remove attribute style:
			child.attributes.remove("style");
		}
		// sub-parsing ...
		cleanStyleProperty(child);
	}
	return true;
}

boolean esvg::Document::parseXMLData(const exml::Element& _root, boolean _isReference) {
	// get the svg version :
	this.version = _root.attributes["version"];
	// parse ...
	Vector2f pos(0,0);
	if (_isReference == false) {
		parseTransform(_root);
		parsePosition(_root, pos, this.size);
		parsePaintAttr(_root);
		Log.verbose("parsed .ROOT trans: " << this.transformMatrix);
	} else {
		Log.verbose("Parse Reference section ... (no attibute)");
	}
	Vector2f maxSize(0,0);
	Vector2f size(0,0);
	// parse all sub node:
	for(auto it : _root.nodes) {
		exml::Element child = it.toElement();
		if (child.exist() == false) {
			// comment can be here...
			continue;
		}
		ememory::SharedPtr<esvg::Base> elementParser;
		if (child.getValue() == "g") {
			elementParser = ememory::makeShared<esvg::Group>(this.paint);
		} else if (child.getValue() == "a") {
			Log.info("Note : 'a' balise is parsed like a g balise ...");
			elementParser = ememory::makeShared<esvg::Group>(this.paint);
		} else if (child.getValue() == "title") {
			this.title = "TODO : set the title here ...";
			continue;
		} else if (child.getValue() == "path") {
			elementParser = ememory::makeShared<esvg::Path>(this.paint);
		} else if (child.getValue() == "rect") {
			elementParser = ememory::makeShared<esvg::Rectangle>(this.paint);
		} else if (child.getValue() == "circle") {
			elementParser = ememory::makeShared<esvg::Circle>(this.paint);
		} else if (child.getValue() == "ellipse") {
			elementParser = ememory::makeShared<esvg::Ellipse>(this.paint);
		} else if (child.getValue() == "line") {
			elementParser = ememory::makeShared<esvg::Line>(this.paint);
		} else if (child.getValue() == "polyline") {
			elementParser = ememory::makeShared<esvg::Polyline>(this.paint);
		} else if (child.getValue() == "polygon") {
			elementParser = ememory::makeShared<esvg::Polygon>(this.paint);
		} else if (child.getValue() == "text") {
			elementParser = ememory::makeShared<esvg::Text>(this.paint);
		} else if (child.getValue() == "radialGradient") {
			if (_isReference == false) {
				Log.error("'" << child.getValue() << "' node must not be defined outside a defs Section");
				continue;
			} else {
				elementParser = ememory::makeShared<esvg::RadialGradient>(this.paint);
			}
		} else if (child.getValue() == "linearGradient") {
			if (_isReference == false) {
				Log.error("'" << child.getValue() << "' node must not be defined outside a defs Section");
				continue;
			} else {
				elementParser = ememory::makeShared<esvg::LinearGradient>(this.paint);
			}
		} else if (child.getValue() == "defs") {
			if (_isReference == true) {
				Log.error("'" << child.getValue() << "' node must not be defined in a defs Section");
				continue;
			} else {
				boolean retRefs = parseXMLData(child, true);
				// TODO : Use retRefs ...
				continue;
			}
		} else if (child.getValue() == "sodipodi:namedview") {
			// Node ignore : generaly inkscape data
			continue;
		} else if (child.getValue() == "metadata") {
			// Node ignore : generaly inkscape data
			continue;
		} else {
			Log.error("(l " << child.getPos() << ") node not suported : '" << child.getValue() << "' must be [title,g,a,path,rect,circle,ellipse,line,polyline,polygon,text,metadata]");
		}
		if (elementParser == null) {
			Log.error("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' allocation error or not supported ...");
			continue;
		}
		if (elementParser->parseXML(child, this.transformMatrix, size) == false) {
			Log.error("(l " << child.getPos() << ") error on node: '" << child.getValue() << "' Sub Parsing ERROR");
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
			this.subElementList.pushBack(elementParser);
		} else {
			this.refList.pushBack(elementParser);
		}
	}
	if (    this.size.x() == 0
	     || this.size.y()==0) {
		this.size.setValue((int)maxSize.x(), (int)maxSize.y());
	} else {
		this.size.setValue((int)this.size.x(), (int)this.size.y());
	}
	if (_isReference == false) {
		displayDebug();
	}
	return true;
}



ememory::SharedPtr<esvg::Base> esvg::Document::getReference(const etk::String& _name) {
	if (_name == "") {
		Log.error("request a reference with no name ... ");
		return null;
	}
	for (auto &it : this.refList) {
		if (it == null) {
			continue;
		}
		if (it->getId() == _name) {
			return it;
		}
	}
	Log.error("Can not find reference name : '" << _name << "'");
	return null;
}

List<etk::Vector<Vector2f>> esvg::Document::getLines(Vector2f _size) {
	List<etk::Vector<Vector2f>> out;
	if (_size.x() <= 0) {
		_size.setX(this.size.x());
	}
	if (_size.y() <= 0) {
		_size.setY(this.size.y());
	}
	Log.debug("lineification size " << _size);
	// create the first element matrix modification ...
	mat2x3 basicTrans;
	basicTrans *= etk::mat2x3Scale(Vector2f(_size.x()/this.size.x(), _size.y()/this.size.y()));
	drawShapePoints(out, 10, 0.25f, basicTrans);
	return out;
}


void esvg::Document::drawShapePoints(List<etk::Vector<Vector2f>>& _out,
                                     int _recurtionMax,
                                     float _threshold,
                                     mat2x3& _basicTrans,
                                     int _level) {
	Log.verbose(spacingDist(_level) << "DRAW shape esvg::Document");
	for (auto &it : this.subElementList) {
		if (it != null) {
			it->drawShapePoints(_out, _recurtionMax, _threshold, _basicTrans, _level+1);
		}
	}
}

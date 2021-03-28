/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/LinearGradient.hpp>
#include <esvg/RadialGradient.hpp>
#include <esvg/render/Path.hpp>
#include <esvg/render/Weight.hpp>
#include <esvg/esvg.hpp>

esvg::RadialGradient::RadialGradient(PaintState _parentPaintState) :
  esvg::Base(_parentPaintState),
  this.center(Vector2f(50,50), esvg::distance_pourcent),
  this.radius(50, esvg::distance_pourcent),
  this.focal(Vector2f(50,50), esvg::distance_pourcent),
  this.unit(gradientUnits_objectBoundingBox),
  this.spread(spreadMethod_pad) {
	
}

esvg::RadialGradient::~RadialGradient() {
	
}


boolean esvg::RadialGradient::parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax) {
	// line must have a minimum size...
	//this.paint.strokeWidth = 1;
	if (_element.exist() == false) {
		return false;
	}
	
	// ---------------- get unique ID ----------------
	this.id = _element.attributes["id"];
	
	//parseTransform(_element);
	//parsePaintAttr(_element);
	
	// add the property of the parrent modifications ...
	this.transformMatrix *= _parentTrans;
	
	etk::String contentX = _element.attributes["cx"];
	etk::String contentY = _element.attributes["cy"];
	if (    contentX != ""
	     && contentY != "") {
		this.center.set(contentX, contentY);
	}
	contentX = _element.attributes["r"];
	if (contentX != "") {
		this.radius.set(contentX);
	}
	contentX = _element.attributes["fx"];
	contentY = _element.attributes["fy"];
	if (    contentX != ""
	     && contentY != "") {
		this.focal.set(contentX, contentY);
	}
	contentX = _element.attributes["gradientUnits"];
	if (contentX == "userSpaceOnUse") {
		this.unit = gradientUnits_userSpaceOnUse;
	} else {
		this.unit = gradientUnits_objectBoundingBox;
		if (    contentX.size() != 0
		     && contentX != "objectBoundingBox") {
			Log.error("Parsing error of 'gradientUnits' ==> not suported value: '" << contentX << "' not in : {userSpaceOnUse/objectBoundingBox} use objectBoundingBox");
		}
	}
	contentX = _element.attributes["spreadMethod"];
	if (contentX == "reflect") {
		this.spread = spreadMethod_reflect;
	} else if (contentX == "repeat") {
		this.spread = spreadMethod_repeat;
	} else {
		this.spread = spreadMethod_pad;
		if (    contentX.size() != 0
		     && contentX != "pad") {
			Log.error("Parsing error of 'spreadMethod' ==> not suported value: '" << contentX << "' not in : {reflect/repeate/pad} use pad");
		}
	}
	// note: xlink:href is incompatible with subNode "stop"
	this.href = _element.attributes["xlink:href"];
	if (this.href.size() != 0) {
		this.href = etk::String(this.href.begin()+1, this.href.end());
	}
	// parse all sub node :
	for(auto it : _element.nodes) {
		exml::Element child = it.toElement();
		if (child.exist() == false) {
			// can be a comment ...
			continue;
		}
		if (child.getValue() == "stop") {
			float offset = 100;
			etk::Color<float,4> stopColor = etk::color::none;
			etk::String content = child.attributes["offset"];
			if (content.size()!=0) {
				Pair<float, enum esvg::distance> tmp = parseLength2(content);
				if (tmp.second == esvg::distance_pixel) {
					// special case ==> all time % then no type define ==> % in [0.0 .. 1.0]
					offset = tmp.first*100.0f;
				} else if (tmp.second != esvg::distance_pourcent) {
					Log.error("offset : " << content << " res=" << tmp.first << "," << tmp.second << " Not support other than pourcent %");
				} else {
					offset = tmp.first;
				}
			}
			content = child.attributes["stop-color"];
			if (content.size()!=0) {
				stopColor = parseColor(content).first;
				Log.verbose(" color : \"" << content << "\"  == > " << stopColor);
			}
			content = child.attributes["stop-opacity"];
			if (content.size()!=0) {
				float opacity = parseLength(content);
				opacity = etk::avg(0.0f, opacity, 1.0f);
				stopColor.setA(opacity);
				Log.verbose(" opacity : '" << content << "'  == > " << stopColor);
			}
			this.data.pushBack(Pair<float, etk::Color<float,4>>(offset, stopColor));
		} else {
			Log.error("(l " << child.getPos() << ") node not suported : '" << child.getValue() << "' must be [stop]");
		}
	}
	if (this.data.size() != 0) {
		if (this.href != "") {
			Log.error("(l " << _element.getPos() << ") node can not have an xlink:href element with sub node named: stop ==> removing href");
			this.href = "";
		}
	}
	return true;
}

void esvg::RadialGradient::display(int _spacing) {
	Log.debug(spacingDist(_spacing) << "RadialGradient center=" << this.center << " focal=" << this.focal << " radius=" << this.radius);
	for (auto &it : this.data) {
		Log.debug(spacingDist(_spacing+1) << "STOP: offset=" << it.first << " color=" << it.second);
	}
}

void esvg::RadialGradient::draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level) {
	Log.verbose(spacingDist(_level) << "DRAW esvg::RadialGradient");
}

const esvg::Dimension& esvg::RadialGradient::getCenter() {
	return this.center;
}

const esvg::Dimension& esvg::RadialGradient::getFocal() {
	return this.focal;
}

const esvg::Dimension1D& esvg::RadialGradient::getRadius() {
	return this.radius;
}

const List<Pair<float, etk::Color<float,4>>>& esvg::RadialGradient::getColors(esvg::Document* _document) {
	if (this.href == "") {
		return this.data;
	}
	if (_document == null) {
		Log.error("Get null input for document");
		return this.data;
	}
	ememory::SharedPtr<esvg::Base> base = _document->getReference(this.href);
	if (base == null) {
		Log.error("Can not get base : '" << this.href << "'");
		return this.data;
	}
	ememory::SharedPtr<esvg::RadialGradient> gradientR = ememory::dynamicPointerCast<esvg::RadialGradient>(base);
	if (gradientR == null) {
		ememory::SharedPtr<esvg::LinearGradient> gradientL = ememory::dynamicPointerCast<esvg::LinearGradient>(base);
		if (gradientL == null) {
			Log.error("Can not cast in a linear/radial gradient: '" << this.href << "' ==> wrong type");
			return this.data;
		}
		return gradientL->getColors(_document);
	}
	return gradientR->getColors(_document);
}




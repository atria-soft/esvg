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

EsvgDocument::Document() {
	this.uri = "";
	this.version = "0.0";
	this.loadOK = false;
	this.size.setValue(0,0);
}

EsvgDocument::~Document() {
	
}



void EsvgDocument::displayDebug() 

void EsvgDocument::draw(Renderer myRenderer, Matrix2x3f basicTrans, int level)
// FOR TEST only ...
void EsvgDocument::generateAnImage(Uri& uri, boolean visualDebug) 
void EsvgDocument::generateAnImage(Vector2i size, Uri& uri, boolean visualDebug) 


List<Color> EsvgDocument::renderImageFloatRGBA(Vector2i size)

List<Color<float,3>> EsvgDocument::renderImageFloatRGB(Vector2i size)
List<Color<uint8t,4>> EsvgDocument::renderImageU8RGBA(Vector2i size)

List<Color<uint8t,3>> EsvgDocument::renderImageU8RGB(Vector2i size)

void EsvgDocument::clear() 

boolean EsvgDocument::parse(String& data)

boolean EsvgDocument::generate(String& data) 

boolean EsvgDocument::load(Uri& uri) 

boolean EsvgDocument::store(Uri& uri) 
boolean EsvgDocument::cleanStyleProperty(XmlElement root) 

boolean EsvgDocument::parseXMLData(XmlElement root, boolean isReference) 



Base EsvgDocument::getReference(String& name)
List<Vector<Vector2f>> EsvgDocument::getLines(Vector2f size)


void EsvgDocument::drawShapePoints(List<Vector<Vector2f>>& out,
                                     int recurtionMax,
                                     float threshold,
                                     Matrix2x3f basicTrans,
                                     int level) 
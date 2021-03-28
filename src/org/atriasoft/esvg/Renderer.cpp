/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/Renderer.hpp>
#include <etk/uri/Uri.hpp>
#include <etk/uri/provider/provider.hpp>

esvg::Renderer::Renderer(const Vector2i& _size, esvg::Document* _document, boolean _visualDebug) :
#ifdef DEBUG
  this.visualDebug(_visualDebug),
  this.factor(1),
#endif
  this.interpolationRecurtionMax(10),
  this.interpolationThreshold(0.25f),
  this.nbSubScanLine(8),
  this.document(_document) {
	#ifdef DEBUG
		if (this.visualDebug == true) {
			this.factor = 20;
		}
	#endif
	setSize(_size);
}

esvg::Renderer::~Renderer() {
	this.buffer.clear();
	this.size = Vector2i(0,0);
}

etk::Color<float,4> esvg::Renderer::mergeColor(etk::Color<float,4> _base, etk::Color<float,4> _integration) {
	etk::Color<float,4> result;
	/*
	if (_integration.a() < _base.a()) {
		result = _integration;
		_integration = _base;
		_base = result;
	}
	*/
	result.setR(_integration.a() * _integration.r() + _base.a() * (1.0f - _integration.a()) * _base.r());
	result.setG(_integration.a() * _integration.g() + _base.a() * (1.0f - _integration.a()) * _base.g());
	result.setB(_integration.a() * _integration.b() + _base.a() * (1.0f - _integration.a()) * _base.b());
	result.setA(_integration.a() + _base.a() * (1.0f - _integration.a()));
	if (result.a() != 0.0f) {
		float reverse = 1.0f/result.a();
		result.setR(result.r()*reverse);
		result.setG(result.g()*reverse);
		result.setB(result.b()*reverse);
	}
	return result;
}

void esvg::Renderer::print(const esvg::render::Weight& _weightFill,
                           ememory::SharedPtr<esvg::render::DynamicColor>& _colorFill,
                           const esvg::render::Weight& _weightStroke,
                           ememory::SharedPtr<esvg::render::DynamicColor>& _colorStroke,
                           float _opacity) {
	if (_colorFill != null) {
		//_colorFill->setViewPort(Pair<Vector2f, Vector2f>(Vector2f(0,0), Vector2f(sizeX, sizeY)));
		_colorFill->generate(this.document);
	}
	if (_colorStroke != null) {
		//_colorStroke->setViewPort(Pair<Vector2f, Vector2f>(Vector2f(0,0), Vector2f(sizeX, sizeY)));
		_colorStroke->generate(this.document);
	}
	// all together
	for (int yyy=0; yyy<this.size.y(); ++yyy) {
		for (int xxx=0; xxx<this.size.x(); ++xxx) {
			Vector2i pos(xxx, yyy);
			float valueFill = _weightFill.get(pos);
			float valueStroke = _weightStroke.get(pos);
			// calculate merge of stroke and fill value:
			etk::Color<float,4> intermediateColorFill(etk::color::none);
			etk::Color<float,4> intermediateColorStroke(etk::color::none);
			if (    _colorFill != null
			     && valueFill != 0.0f) {
				intermediateColorFill = _colorFill->getColor(pos);
				intermediateColorFill.setA(intermediateColorFill.a()*valueFill);
			}
			if (    _colorStroke != null
			     && valueStroke != 0.0f) {
				intermediateColorStroke = _colorStroke->getColor(pos);
				intermediateColorStroke.setA(intermediateColorStroke.a()*valueStroke);
			}
			etk::Color<float,4> intermediateColor = mergeColor(intermediateColorFill, intermediateColorStroke);
			intermediateColor.setA(intermediateColor.a() * _opacity);
			#if DEBUG
				for (int deltaY=0; deltaY<this.factor; ++deltaY) {
					for (int deltaX=0; deltaX<this.factor; ++deltaX) {
						int id = this.size.x()*this.factor*(yyy*this.factor+deltaY) + (xxx*this.factor+deltaX);
						this.buffer[id] = mergeColor(this.buffer[id], intermediateColor);
					}
				}
			#else
				this.buffer[this.size.x()*yyy + xxx] = mergeColor(this.buffer[this.size.x()*yyy + xxx], intermediateColor);
			#endif
		}
	}
	#ifdef DEBUG
		// display the gradient position:
		ememory::SharedPtr<esvg::render::DynamicColorSpecial> tmpColor = ememory::dynamicPointerCast<esvg::render::DynamicColorSpecial>(_colorFill);
		if (tmpColor != null) {
			esvg::render::SegmentList listSegment;
			// Display bounding box
			listSegment.addSegment(esvg::render::Point(tmpColor->this.viewPort.first),
			                       esvg::render::Point(Vector2f(tmpColor->this.viewPort.first.x(), tmpColor->this.viewPort.second.y()) ),
			                       false);
			listSegment.addSegment(esvg::render::Point(Vector2f(tmpColor->this.viewPort.first.x(), tmpColor->this.viewPort.second.y()) ),
			                       esvg::render::Point(tmpColor->this.viewPort.second),
			                       false);
			listSegment.addSegment(esvg::render::Point(tmpColor->this.viewPort.second),
			                       esvg::render::Point(Vector2f(tmpColor->this.viewPort.second.x(), tmpColor->this.viewPort.first.y()) ),
			                       false);
			listSegment.addSegment(esvg::render::Point(Vector2f(tmpColor->this.viewPort.second.x(), tmpColor->this.viewPort.first.y()) ),
			                       esvg::render::Point(tmpColor->this.viewPort.first),
			                       false);
			listSegment.applyMatrix(tmpColor->this.matrix);
			// display the gradient axis
			listSegment.addSegment(esvg::render::Point(tmpColor->this.pos1),
			                       esvg::render::Point(tmpColor->this.pos2),
			                       false);
			/*
				mat2x3 this.matrix;
				Pair<Vector2f, Vector2f> this.viewPort;
				Vector2f this.pos1;
				Vector2f this.pos2;
			*/
			addDebugSegment(listSegment);
		}
	#endif
}

#ifdef DEBUG
	void esvg::Renderer::addDebugSegment(const esvg::render::SegmentList& _listSegment) {
		if (this.visualDebug == false) {
			return;
		}
		Vector2i dynamicSize = this.size * this.factor;
		// for each lines:
		for (int yyy=0; yyy<dynamicSize.y(); ++yyy) {
			// Reduce the number of lines in the subsampling parsing:
			List<esvg::render::Segment> availlableSegmentPixel;
			for (auto &it : _listSegment.this.data) {
				if (    it.p0.y() * this.factor <= float(yyy+1)
				     && it.p1.y() * this.factor >= float(yyy)) {
					availlableSegmentPixel.pushBack(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = yyy + 0.5f;
			List<esvg::render::Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    it.p0.y() * this.factor <= subSamplingCenterPos
				     && it.p1.y() * this.factor >= subSamplingCenterPos ) {
					availlableSegment.pushBack(it);
				}
			}
			// x position, angle
			List<Pair<float, float>> listPosition;
			for (auto &it : availlableSegment) {
				Vector2f delta = it.p0 * this.factor - it.p1 * this.factor;
				// x = coefficent*y+bbb;
				float coefficient = delta.x()/delta.y();
				float bbb = it.p0.x() * this.factor - coefficient*it.p0.y() * this.factor;
				float xpos = coefficient * subSamplingCenterPos + bbb;
				if (    xpos >= 0
				     && xpos < dynamicSize.x()
				     && yyy >= 0
				     && yyy < dynamicSize.y() ) {
					if (it.direction == 1.0f) {
						this.buffer[(dynamicSize.x()*yyy + int(xpos))] = etk::color::blue;
					} else {
						this.buffer[(dynamicSize.x()*yyy + int(xpos))] = etk::color::darkRed;
					}
				}
			}
		}
		// for each colomn:
		for (int xxx=0; xxx<dynamicSize.x(); ++xxx) {
			// Reduce the number of lines in the subsampling parsing:
			List<esvg::render::Segment> availlableSegmentPixel;
			for (auto &it : _listSegment.this.data) {
				if (    (    it.p0.x() * this.factor <= float(xxx+1)
				          && it.p1.x() * this.factor >= float(xxx) )
				     || (    it.p0.x() * this.factor >= float(xxx+1)
				          && it.p1.x() * this.factor <= float(xxx) ) ) {
					availlableSegmentPixel.pushBack(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			float subSamplingCenterPos = xxx + 0.5f;
			List<esvg::render::Segment> availlableSegment;
			// find in the subList ...
			for (auto &it : availlableSegmentPixel) {
				if (    (    it.p0.x() * this.factor <= subSamplingCenterPos
				          && it.p1.x() * this.factor >= subSamplingCenterPos)
				     || (    it.p0.x() * this.factor >= subSamplingCenterPos
				          && it.p1.x() * this.factor <= subSamplingCenterPos) ) {
					availlableSegment.pushBack(it);
				}
			}
			// x position, angle
			List<Pair<float, float>> listPosition;
			for (auto &it : availlableSegment) {
				Vector2f delta = it.p0 * this.factor - it.p1 * this.factor;
				// x = coefficent*y+bbb;
				if (delta.x() == 0) {
					continue;
				}
				float coefficient = delta.y()/delta.x();
				float bbb = it.p0.y() * this.factor - coefficient*it.p0.x() * this.factor;
				float ypos = coefficient * subSamplingCenterPos + bbb;
				if (    ypos >= 0
				     && ypos < dynamicSize.y()
				     && xxx >= 0
				     && xxx < dynamicSize.y() ) {
					if (it.direction == 1.0f) {
						this.buffer[(dynamicSize.x()*int(ypos) + xxx)] = etk::color::blue;
					} else {
						this.buffer[(dynamicSize.x()*int(ypos) + xxx)] = etk::color::darkRed;
					}
				}
			}
		}
	}
#endif


void esvg::Renderer::writePPM(const etk::Uri& _uri) {
	if (this.buffer.size() == 0) {
		return;
	}
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		Log.error("Can not create the uri: " << _uri);
		return;
	}
	if (fileIo->open(etk::io::OpenMode::Write) == false) {
		Log.error("Can not open (r) the file : " << _uri);
		return;
	}
	int sizeX = this.size.x();
	int sizeY = this.size.y();
	#if DEBUG
		sizeX *= this.factor;
		sizeY *= this.factor;
	#endif
	Log.debug("Generate ppm : " << this.size << " debug size=" << Vector2i(sizeX,sizeY));
	char tmpValue[1024];
	sprintf(tmpValue, "P6 %d %d 255 ", sizeX, sizeY);
	fileIo->write(tmpValue,1,sizeof(tmpValue));
	for (int iii=0 ; iii<sizeX*sizeY; iii++) {
		etk::Color<uint8_t,3> tmp = this.buffer[iii];
		fileIo->write(&tmp, 1, 3);
	}
	fileIo->close();
}
#define PLOPPP
extern "C" {
	#pragma pack(push,1)
	struct bitmapFileHeader {
		int16_t bfType;
		int bfSize;
		int bfReserved;
		int bfOffBits;
	};
	struct bitmapInfoHeader {
		int biSize;
		int biWidth;
		int biHeight;
		int16_t biPlanes;
		int16_t biBitCount;
		int biCompression;
		int biSizeImage;
		int biXPelsPerMeter;
		int biYPelsPerMeter;
		#ifndef PLOPPP
		int biClrUsed;
		int biClrImportant;
		#else
		// https://en.wikipedia.org/wiki/BMP_file_format / example 2
		int biPaletteNumber;
		int biImportantColor;
		int biBitMaskRed;
		int biBitMaskGreen;
		int biBitMaskBlue;
		int biBitMaskAlpha;
		int biLCSColorSpace;
		int biUnused[16];
		#endif
	};
	#pragma pack(pop)
}
void esvg::Renderer::writeBMP(const etk::Uri& _uri) {
	if (this.buffer.size() == 0) {
		return;
	}
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		Log.error("Can not create the uri: " << _uri);
		return;
	}
	if (fileIo->open(etk::io::OpenMode::Write) == false) {
		Log.error("Can not open (r) the file : " << _uri);
		return;
	}
	struct bitmapFileHeader fileHeader;
	struct bitmapInfoHeader infoHeader;
	
	int sizeX = this.size.x();
	int sizeY = this.size.y();
	#if DEBUG
		sizeX *= this.factor;
		sizeY *= this.factor;
	#endif
	
	fileHeader.bfType = 0x4D42;
	fileHeader.bfSize = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader) + sizeX*sizeY*4;
	fileHeader.bfReserved = 0;
	fileHeader.bfOffBits = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader);
	
	
	infoHeader.biSize = sizeof(struct bitmapInfoHeader);
	infoHeader.biWidth = sizeX;
	infoHeader.biHeight = sizeY;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 32;
	#ifndef PLOPPP
	infoHeader.biCompression = 0;
	#else
	infoHeader.biCompression = 3;
	#endif
	infoHeader.biSizeImage = sizeX*sizeY*4;
	infoHeader.biXPelsPerMeter = 75;
	infoHeader.biYPelsPerMeter = 75;
	#ifndef PLOPPP
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	#else
	infoHeader.biPaletteNumber = 0;
	infoHeader.biImportantColor = 0;
	infoHeader.biBitMaskRed = 0xFF000000;
	infoHeader.biBitMaskGreen = 0x00FF0000;
	infoHeader.biBitMaskBlue =0x0000FF00;
	infoHeader.biBitMaskAlpha = 0x000000FF;
	infoHeader.biLCSColorSpace = 0x73524742; // "Win "
	for (int jjj=0; jjj<16; ++jjj) {
		infoHeader.biUnused[jjj] = 0;
	}
	infoHeader.biUnused[12] = 0x00000002;
	#endif
	// get the data : 
	fileIo->write(&fileHeader, sizeof(struct bitmapFileHeader), 1);
	fileIo->write(&infoHeader, sizeof(struct bitmapInfoHeader), 1);
	
	uint8_t data[16];
	for(int yyy=sizeY-1; yyy>=0; --yyy) {
		for(int xxx=0; xxx<sizeX; ++xxx) {
			const etk::Color<uint8_t,4>& tmpColor = this.buffer[sizeX*yyy + xxx];
			uint8_t* pointer = data;
			#ifndef PLOPPP
			*pointer++ = tmpColor.a();
			*pointer++ = tmpColor.r();
			*pointer++ = tmpColor.g();
			*pointer++ = tmpColor.b();
			#else
			*pointer++ = tmpColor.a();
			*pointer++ = tmpColor.b();
			*pointer++ = tmpColor.g();
			*pointer++ = tmpColor.r();
			#endif
			fileIo->write(data,1,4);
		}
	}
	fileIo->close();
}


void esvg::Renderer::setSize(const Vector2i& _size) {
	this.size = _size;
	this.buffer.resize(this.size.x() * this.size.y()
	#if DEBUG
	  * this.factor * this.factor
	#endif
	  , etk::color::none);
}

const Vector2i& esvg::Renderer::getSize() const {
	return this.size;
}

List<etk::Color<float,4>> esvg::Renderer::getData() {
	return this.buffer;
}




void esvg::Renderer::setInterpolationRecurtionMax(int _value) {
	this.interpolationRecurtionMax = etk::avg(1, _value, 200);
}

int esvg::Renderer::getInterpolationRecurtionMax() const {
	return this.interpolationRecurtionMax;
}

void esvg::Renderer::setInterpolationThreshold(float _value) {
	this.interpolationThreshold = etk::avg(0.0f, _value, 20000.0f);
}

float esvg::Renderer::getInterpolationThreshold() const {
	return this.interpolationThreshold;
}

void esvg::Renderer::setNumberSubScanLine(int _value) {
	this.nbSubScanLine = etk::avg(1, _value, 200);
}

int esvg::Renderer::getNumberSubScanLine() const {
	return this.nbSubScanLine;
}



/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/render/DynamicColor.hpp>
#include <esvg/LinearGradient.hpp>
#include <esvg/RadialGradient.hpp>
#include <esvg/esvg.hpp>

esvg::render::DynamicColorSpecial::DynamicColorSpecial(const etk::String& _link, const mat2x3& _mtx) :
  this.linear(true),
  this.colorName(_link),
  this.matrix(_mtx),
  this.viewPort(Vector2f(9999999999.0,9999999999.0),Vector2f(-9999999999.0,-9999999999.0)) {
	
}

void esvg::render::DynamicColorSpecial::setViewPort(const Pair<Vector2f, Vector2f>& _viewPort) {
	this.viewPort = _viewPort;
}


static Vector2f getIntersect(const Vector2f& _point1,
                         const Vector2f& _vect1,
                         const Vector2f& _point2,
                         const Vector2f& _vect2) {
	float diviseur = _vect1.x() * _vect2.y() - _vect1.y() * _vect2.x();
	if(diviseur != 0.0f) {
		float mmm = (   _vect1.x() * _point1.y()
		              - _vect1.x() * _point2.y()
		              - _vect1.y() * _point1.x()
		              + _vect1.y() * _point2.x()
		            ) / diviseur;
		return Vector2f(_point2 + _vect2 * mmm);
	}
	Log.error("Get divider / 0.0f");
	return _point2;
}

etk::Color<float,4> esvg::render::DynamicColorSpecial::getColor(const Vector2i& _pos) const {
	if (this.data.size() < 2) {
		return etk::color::purple;
	}
	if (this.linear == true) {
		return getColorLinear(_pos);
	} else {
		return getColorRadial(_pos);
	}
	return etk::color::purple;
}

etk::Color<float,4> esvg::render::DynamicColorSpecial::getColorLinear(const Vector2i& _pos) const {
	float ratio = 0.0f;
	if (this.unit == gradientUnits_userSpaceOnUse) {
		Vector2f vectorBase = this.pos2 - this.pos1;
		Vector2f vectorOrtho(vectorBase.y(), -vectorBase.x());
		Vector2f intersec = getIntersect(this.pos1,                   vectorBase,
		                             Vector2f(_pos.x(), _pos.y()), vectorOrtho);
		float baseSize = vectorBase.length();
		Vector2f vectorBaseDraw = intersec - this.pos1;
		float baseDraw = vectorBaseDraw.length();
		ratio = baseDraw / baseSize;
		switch(this.spread) {
			case spreadMethod_pad:
				if (vectorBase.dot(vectorBaseDraw) < 0) {
					ratio *= -1.0;
				}
				break;
			case spreadMethod_reflect:
				ratio -= float((int(ratio)>>1)<<1);
				if (ratio > 1.0f) {
					ratio = 2.0f-ratio;
				}
				break;
			case spreadMethod_repeat:
				if (vectorBase.dot(vectorBaseDraw) < 0) {
					ratio *= -1.0;
				}
				ratio -= float(int(ratio));
				if (ratio <0.0f) {
					#ifndef __STDCPP_LLVM__
						ratio = 1.0f-etk::abs(ratio);
					#else
						ratio = 1.0f-abs(ratio);
					#endif
				}
				break;
		}
	} else {
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		Vector2f intersecX = getIntersect(this.pos1,                   this.axeX,
		                              Vector2f(_pos.x(), _pos.y()), this.axeY);
		Vector2f intersecY = getIntersect(this.pos1,                   this.axeY,
		                              Vector2f(_pos.x(), _pos.y()), this.axeX);
		Vector2f vectorBaseDrawX = intersecX - this.pos1;
		Vector2f vectorBaseDrawY = intersecY - this.pos1;
		float baseDrawX = vectorBaseDrawX.length();
		float baseDrawY = vectorBaseDrawY.length();
		if (this.axeX.dot(vectorBaseDrawX) < 0) {
			baseDrawX *= -1.0f;
		}
		if (this.axeY.dot(vectorBaseDrawY) < 0) {
			baseDrawY *= -1.0f;
		}
		if (this.baseSize.x()+this.baseSize.y() != 0.0f) {
			if (    this.baseSize.x() != 0.0f
			     && this.baseSize.y() != 0.0f) {
				ratio = (baseDrawX*this.baseSize.y() + baseDrawY*this.baseSize.x())/(this.baseSize.x()*this.baseSize.y()*2.0f);
			} else if (this.baseSize.x() != 0.0f) {
				ratio = baseDrawX/this.baseSize.x();
			} else {
				ratio = baseDrawY/this.baseSize.y();
			}
		} else {
			ratio = 1.0f;
		}
		switch(this.spread) {
			case spreadMethod_pad:
				// nothing to do ...
				break;
			case spreadMethod_reflect:
				#ifndef __STDCPP_LLVM__
					ratio = etk::abs(ratio);
				#else
					ratio = abs(ratio);
				#endif
				ratio -= float((int(ratio)>>1)<<1);
				if (ratio > 1.0f) {
					ratio = 2.0f-ratio;
				}
				break;
			case spreadMethod_repeat:
				ratio -= float(int(ratio));
				if (ratio <0.0f) {
					#ifndef __STDCPP_LLVM__
						ratio = 1.0f-etk::abs(ratio);
					#else
						ratio = 1.0f-abs(ratio);
					#endif
				}
				break;
		}
	}
	if (ratio <= this.data[0].first*0.01f) {
		return this.data[0].second;
	}
	if (ratio >= this.data.back().first*0.01f) {
		return this.data.back().second;
	}
	for (size_t iii=1; iii<this.data.size(); ++iii) {
		if (ratio <= this.data[iii].first*0.01f) {
			float localRatio = ratio - this.data[iii-1].first*0.01f;
			localRatio = localRatio / ((this.data[iii].first - this.data[iii-1].first) * 0.01f);
			return etk::Color<float,4>(this.data[iii-1].second.r() * (1.0-localRatio) + this.data[iii].second.r() * localRatio,
			                           this.data[iii-1].second.g() * (1.0-localRatio) + this.data[iii].second.g() * localRatio,
			                           this.data[iii-1].second.b() * (1.0-localRatio) + this.data[iii].second.b() * localRatio,
			                           this.data[iii-1].second.a() * (1.0-localRatio) + this.data[iii].second.a() * localRatio);
		}
	}
	return etk::color::green;
}
static Pair<Vector2f,Vector2f> intersectLineToCircle(const Vector2f& _pos1,
                                                  const Vector2f& _pos2,
                                                  const Vector2f& _center = Vector2f(0.0f, 0.0f),
                                                  float _radius = 1.0f) {
	Vector2f v1;
	Vector2f v2;
	//vector2D from point 1 to point 2
	v1 = _pos2 - _pos1;
	//vector2D from point 1 to the circle's center
	v2 = _center - _pos1;
	
	float dot = v1.dot(v2);
	Vector2f proj1 = Vector2f(((dot / (v1.length2())) * v1.x()),
	                  ((dot / (v1.length2())) * v1.y()));
	Vector2f midpt = _pos1 + proj1;
	
	float distToCenter = (midpt - _center).length2();
	if (distToCenter > _radius * _radius) {
		return Pair<Vector2f,Vector2f>(Vector2f(0.0,0.0), Vector2f(0.0,0.0));
	}
	if (distToCenter == _radius * _radius) {
		return Pair<Vector2f,Vector2f>(midpt, midpt);
	}
	float distToIntersection;
	if (distToCenter == 0.0f) {
		distToIntersection = _radius;
	} else {
		#ifndef __STDCPP_LLVM__
			distToCenter = etk::sqrt(distToCenter);
			distToIntersection = etk::sqrt(_radius * _radius - distToCenter * distToCenter);
		#else
			distToCenter = sqrtf(distToCenter);
			distToIntersection = sqrtf(_radius * _radius - distToCenter * distToCenter);
		#endif
	}
	// normalize...
	v1.safeNormalize();
	v1 *= distToIntersection;
	return Pair<Vector2f,Vector2f>(midpt + v1, midpt - v1);
}

etk::Color<float,4> esvg::render::DynamicColorSpecial::getColorRadial(const Vector2i& _pos) const {
	float ratio = 0.0f;
	// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object)..
	Vector2f intersecX = getIntersect(this.pos1,                   this.axeX,
	                              Vector2f(_pos.x(), _pos.y()), this.axeY);
	Vector2f intersecY = getIntersect(this.pos1,                   this.axeY,
	                              Vector2f(_pos.x(), _pos.y()), this.axeX);
	Vector2f vectorBaseDrawX = intersecX - this.pos1;
	Vector2f vectorBaseDrawY = intersecY - this.pos1;
	float baseDrawX = vectorBaseDrawX.length();
	float baseDrawY = vectorBaseDrawY.length();
	// specal case when focal == center (this is faster ...)
	if (this.centerIsFocal == true) {
		ratio = Vector2f(baseDrawX, baseDrawY).length();
		if (this.baseSize.x()+this.baseSize.y() != 0.0f) {
			if (    this.baseSize.x() != 0.0f
			     && this.baseSize.y() != 0.0f) {
				ratio = Vector2f(baseDrawX/this.baseSize.x(), baseDrawY/this.baseSize.y()).length();
			} else if (this.baseSize.x() != 0.0f) {
				ratio = baseDrawX/this.baseSize.x();
			} else {
				ratio = baseDrawY/this.baseSize.y();
			}
		} else {
			ratio = 1.0f;
		}
	} else {
		// set the sense of the elements:
		if (this.axeX.dot(vectorBaseDrawX) < 0) {
			baseDrawX *= -1.0f;
		}
		if (this.axeY.dot(vectorBaseDrawY) < 0) {
			baseDrawY *= -1.0f;
		}
		if (this.baseSize.y() != 0.0f) {
			baseDrawY /= this.baseSize.y();
		}
		// normalize to 1.0f
		baseDrawX /= this.baseSize.x();
		if (    this.clipOut == true
		     && baseDrawX <= -1.0f) {
			ratio = 1.0f;
		} else {
			float tmpLength = -this.focalLength/this.baseSize.x();
			Vector2f focalCenter = Vector2f(tmpLength, 0.0f);
			Vector2f currentPoint = Vector2f(baseDrawX, baseDrawY);
			if (focalCenter == currentPoint) {
				ratio = 0.0f;
			} else {
				Pair<Vector2f,Vector2f> positions = intersectLineToCircle(focalCenter, currentPoint);
				float lenghtBase = (currentPoint - focalCenter).length();
				float lenghtBorder1 = (positions.first - focalCenter).length();
				float lenghtBorder2 = (positions.second - focalCenter).length();
				ratio = lenghtBase/lenghtBorder1;
			}
		}
	}
	switch(this.spread) {
		case spreadMethod_pad:
			// nothing to do ...
			break;
		case spreadMethod_reflect:
			ratio -= float((int(ratio)>>1)<<1);
			if (ratio > 1.0f) {
				ratio = 2.0f-ratio;
			}
			break;
		case spreadMethod_repeat:
			ratio -= float(int(ratio));
			if (ratio <0.0f) {
				#ifndef __STDCPP_LLVM__
					ratio = 1.0f-etk::abs(ratio);
				#else
					ratio = 1.0f-abs(ratio);
				#endif
			}
			break;
	}
	if (ratio <= this.data[0].first*0.01f) {
		return this.data[0].second;
	}
	if (ratio >= this.data.back().first*0.01f) {
		return this.data.back().second;
	}
	for (size_t iii=1; iii<this.data.size(); ++iii) {
		if (ratio <= this.data[iii].first*0.01f) {
			float localRatio = ratio - this.data[iii-1].first*0.01f;
			localRatio = localRatio / ((this.data[iii].first - this.data[iii-1].first) * 0.01f);
			return etk::Color<float,4>(this.data[iii-1].second.r() * (1.0-localRatio) + this.data[iii].second.r() * localRatio,
			                           this.data[iii-1].second.g() * (1.0-localRatio) + this.data[iii].second.g() * localRatio,
			                           this.data[iii-1].second.b() * (1.0-localRatio) + this.data[iii].second.b() * localRatio,
			                           this.data[iii-1].second.a() * (1.0-localRatio) + this.data[iii].second.a() * localRatio);
		}
	}
	return etk::color::green;
}


void esvg::render::DynamicColorSpecial::generate(esvg::Document* _document) {
	if (_document == null) {
		Log.error("Get null input for document");
		return;
	}
	ememory::SharedPtr<esvg::Base> base = _document->getReference(this.colorName);
	if (base == null) {
		Log.error("Can not get base : '" << this.colorName << "'");
		return;
	}
	// Now we can know if we use linear or radial gradient ...
	ememory::SharedPtr<esvg::LinearGradient> gradient = ememory::dynamicPointerCast<esvg::LinearGradient>(base);
	if (gradient != null) {
		this.linear = true;
		Log.verbose("get for color linear:");
		gradient->display(2);
		this.unit = gradient->this.unit;
		this.spread = gradient->this.spread;
		Log.verbose("    viewport = {" << this.viewPort.first << "," << this.viewPort.second << "}");
		Vector2f size = this.viewPort.second - this.viewPort.first;
		
		esvg::Dimension dimPos1 = gradient->getPosition1();
		this.pos1 = dimPos1.getPixel(size);
		if (dimPos1.getType() == esvg::distance_pourcent) {
			this.pos1 += this.viewPort.first;
		}
		esvg::Dimension dimPos2 = gradient->getPosition2();
		this.pos2 = dimPos2.getPixel(size);
		if (dimPos2.getType() == esvg::distance_pourcent) {
			this.pos2 += this.viewPort.first;
		}
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		Vector2f delta = this.pos2 - this.pos1;
		if (delta.x() < 0.0f) {
			this.axeX = Vector2f(-1.0f, 0.0f);
		} else {
			this.axeX = Vector2f(1.0f, 0.0f);
		}
		if (delta.y() < 0.0f) {
			this.axeY = Vector2f(0.0f, -1.0f);
		} else {
			this.axeY = Vector2f(0.0f, 1.0f);
		}
		// Move the positions ...
		this.pos1 = this.matrix * this.pos1;
		this.pos2 = this.matrix * this.pos2;
		this.axeX = this.matrix.applyScaleRotation(this.axeX);
		this.axeY = this.matrix.applyScaleRotation(this.axeY);
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		Vector2f intersecX = getIntersect(this.pos1, this.axeX,
		                              this.pos2, this.axeY);
		Vector2f intersecY = getIntersect(this.pos1, this.axeY,
		                              this.pos2, this.axeX);
		this.baseSize = Vector2f((this.pos1 - intersecX).length(),
		                  (this.pos1 - intersecY).length());
		// get all the colors
		this.data = gradient->getColors(_document);
	} else {
		this.linear = false;
		ememory::SharedPtr<esvg::RadialGradient> gradient = ememory::dynamicPointerCast<esvg::RadialGradient>(base);
		if (gradient == null) {
			Log.error("Can not cast in a linear gradient: '" << this.colorName << "' ==> wrong type");
			return;
		}
		Log.verbose("get for color Radial:");
		gradient->display(2);
		this.unit = gradient->this.unit;
		this.spread = gradient->this.spread;
		Log.verbose("    viewport = {" << this.viewPort.first << "," << this.viewPort.second << "}");
		Vector2f size = this.viewPort.second - this.viewPort.first;
		
		esvg::Dimension dimCenter = gradient->getCenter();
		Vector2f center = dimCenter.getPixel(size);
		if (dimCenter.getType() == esvg::distance_pourcent) {
			center += this.viewPort.first;
		}
		esvg::Dimension dimFocal = gradient->getFocal();
		Vector2f focal = dimFocal.getPixel(size);
		if (dimFocal.getType() == esvg::distance_pourcent) {
			focal += this.viewPort.first;
		}
		esvg::Dimension1D dimRadius = gradient->getRadius();
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object)..
		if (center == focal) {
			this.centerIsFocal = true;
			this.pos2.setX(dimRadius.getPixel(size.x()));
			this.pos2.setY(dimRadius.getPixel(size.y()));
			this.pos2 += center;
			Vector2f delta = center - this.pos2;
			if (delta.x() < 0.0f) {
				this.axeX = Vector2f(-1.0f, 0.0f);
			} else {
				this.axeX = Vector2f(1.0f, 0.0f);
			}
			if (delta.y() < 0.0f) {
				this.axeY = Vector2f(0.0f, -1.0f);
			} else {
				this.axeY = Vector2f(0.0f, 1.0f);
			}
			this.pos1 = center;
		} else {
			this.centerIsFocal = false;
			this.axeX = (center - focal).safeNormalize();
			this.axeY = Vector2f(this.axeX.y(), -this.axeX.x());
			
			this.pos2 = this.axeX * dimRadius.getPixel(size.x()) + this.axeY * dimRadius.getPixel(size.y());
			this.pos2 += center;
			this.pos1 = center;
		}
		// Move the positions ...
		this.pos1 = this.matrix * this.pos1;
		center = this.matrix * center;
		this.pos2 = this.matrix * this.pos2;
		this.axeX = this.matrix.applyScaleRotation(this.axeX);
		this.axeY = this.matrix.applyScaleRotation(this.axeY);
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		Vector2f intersecX = getIntersect(this.pos1, this.axeX,
		                              this.pos2, this.axeY);
		Vector2f intersecY = getIntersect(this.pos1, this.axeY,
		                              this.pos2, this.axeX);
		this.baseSize = Vector2f((intersecX - this.pos1).length(),
		                  (intersecY - this.pos1).length());
		if (this.centerIsFocal == false) {
			this.focalLength = (center - this.matrix * focal).length();
			if (this.focalLength >= this.baseSize.x()) {
				Log.debug("Change position of the Focal ... ==> set it inside the circle");
				this.focalLength = this.baseSize.x()*0.999998f;
				this.clipOut = true;
			} else {
				this.clipOut = false;
			}
		}
		Log.verbose("baseSize=" << this.baseSize << " this.pos1=" << this.pos1 << " dim=" << dimCenter << " this.focal=" << this.focal << " this.pos2=" << this.pos2 << " dim=" << dimRadius);
		// get all the colors
		this.data = gradient->getColors(_document);
	}
}

ememory::SharedPtr<esvg::render::DynamicColor> esvg::render::createColor(Pair<etk::Color<float,4>, etk::String> _color, const mat2x3& _mtx) {
	// Check if need to create a color:
	if (    _color.first.a() == 0x00
	     && _color.second == "") {
	     return null;
	}
	if (_color.second != "") {
		return ememory::makeShared<esvg::render::DynamicColorSpecial>(_color.second, _mtx);
	}
	return ememory::makeShared<esvg::render::DynamicColorUni>(_color.first);
}

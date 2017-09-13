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
  m_linear(true),
  m_colorName(_link),
  m_matrix(_mtx),
  m_viewPort(vec2(9999999999.0,9999999999.0),vec2(-9999999999.0,-9999999999.0)) {
	
}

void esvg::render::DynamicColorSpecial::setViewPort(const etk::Pair<vec2, vec2>& _viewPort) {
	m_viewPort = _viewPort;
}


static vec2 getIntersect(const vec2& _point1,
                         const vec2& _vect1,
                         const vec2& _point2,
                         const vec2& _vect2) {
	float diviseur = _vect1.x() * _vect2.y() - _vect1.y() * _vect2.x();
	if(diviseur != 0.0f) {
		float mmm = (   _vect1.x() * _point1.y()
		              - _vect1.x() * _point2.y()
		              - _vect1.y() * _point1.x()
		              + _vect1.y() * _point2.x()
		            ) / diviseur;
		return vec2(_point2 + _vect2 * mmm);
	}
	ESVG_ERROR("Get divider / 0.0f");
	return _point2;
}

etk::Color<float,4> esvg::render::DynamicColorSpecial::getColor(const ivec2& _pos) const {
	if (m_data.size() < 2) {
		return etk::color::purple;
	}
	if (m_linear == true) {
		return getColorLinear(_pos);
	} else {
		return getColorRadial(_pos);
	}
	return etk::color::purple;
}

etk::Color<float,4> esvg::render::DynamicColorSpecial::getColorLinear(const ivec2& _pos) const {
	float ratio = 0.0f;
	if (m_unit == gradientUnits_userSpaceOnUse) {
		vec2 vectorBase = m_pos2 - m_pos1;
		vec2 vectorOrtho(vectorBase.y(), -vectorBase.x());
		vec2 intersec = getIntersect(m_pos1,                   vectorBase,
		                             vec2(_pos.x(), _pos.y()), vectorOrtho);
		float baseSize = vectorBase.length();
		vec2 vectorBaseDraw = intersec - m_pos1;
		float baseDraw = vectorBaseDraw.length();
		ratio = baseDraw / baseSize;
		switch(m_spread) {
			case spreadMethod_pad:
				if (vectorBase.dot(vectorBaseDraw) < 0) {
					ratio *= -1.0;
				}
				break;
			case spreadMethod_reflect:
				ratio -= float((int32_t(ratio)>>1)<<1);
				if (ratio > 1.0f) {
					ratio = 2.0f-ratio;
				}
				break;
			case spreadMethod_repeat:
				if (vectorBase.dot(vectorBaseDraw) < 0) {
					ratio *= -1.0;
				}
				ratio -= float(int32_t(ratio));
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
		vec2 intersecX = getIntersect(m_pos1,                   m_axeX,
		                              vec2(_pos.x(), _pos.y()), m_axeY);
		vec2 intersecY = getIntersect(m_pos1,                   m_axeY,
		                              vec2(_pos.x(), _pos.y()), m_axeX);
		vec2 vectorBaseDrawX = intersecX - m_pos1;
		vec2 vectorBaseDrawY = intersecY - m_pos1;
		float baseDrawX = vectorBaseDrawX.length();
		float baseDrawY = vectorBaseDrawY.length();
		if (m_axeX.dot(vectorBaseDrawX) < 0) {
			baseDrawX *= -1.0f;
		}
		if (m_axeY.dot(vectorBaseDrawY) < 0) {
			baseDrawY *= -1.0f;
		}
		if (m_baseSize.x()+m_baseSize.y() != 0.0f) {
			if (    m_baseSize.x() != 0.0f
			     && m_baseSize.y() != 0.0f) {
				ratio = (baseDrawX*m_baseSize.y() + baseDrawY*m_baseSize.x())/(m_baseSize.x()*m_baseSize.y()*2.0f);
			} else if (m_baseSize.x() != 0.0f) {
				ratio = baseDrawX/m_baseSize.x();
			} else {
				ratio = baseDrawY/m_baseSize.y();
			}
		} else {
			ratio = 1.0f;
		}
		switch(m_spread) {
			case spreadMethod_pad:
				// nothing to do ...
				break;
			case spreadMethod_reflect:
				#ifndef __STDCPP_LLVM__
					ratio = etk::abs(ratio);
				#else
					ratio = abs(ratio);
				#endif
				ratio -= float((int32_t(ratio)>>1)<<1);
				if (ratio > 1.0f) {
					ratio = 2.0f-ratio;
				}
				break;
			case spreadMethod_repeat:
				ratio -= float(int32_t(ratio));
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
	if (ratio <= m_data[0].first*0.01f) {
		return m_data[0].second;
	}
	if (ratio >= m_data.back().first*0.01f) {
		return m_data.back().second;
	}
	for (size_t iii=1; iii<m_data.size(); ++iii) {
		if (ratio <= m_data[iii].first*0.01f) {
			float localRatio = ratio - m_data[iii-1].first*0.01f;
			localRatio = localRatio / ((m_data[iii].first - m_data[iii-1].first) * 0.01f);
			return etk::Color<float,4>(m_data[iii-1].second.r() * (1.0-localRatio) + m_data[iii].second.r() * localRatio,
			                           m_data[iii-1].second.g() * (1.0-localRatio) + m_data[iii].second.g() * localRatio,
			                           m_data[iii-1].second.b() * (1.0-localRatio) + m_data[iii].second.b() * localRatio,
			                           m_data[iii-1].second.a() * (1.0-localRatio) + m_data[iii].second.a() * localRatio);
		}
	}
	return etk::color::green;
}
static etk::Pair<vec2,vec2> intersectLineToCircle(const vec2& _pos1,
                                                  const vec2& _pos2,
                                                  const vec2& _center = vec2(0.0f, 0.0f),
                                                  float _radius = 1.0f) {
	vec2 v1;
	vec2 v2;
	//vector2D from point 1 to point 2
	v1 = _pos2 - _pos1;
	//vector2D from point 1 to the circle's center
	v2 = _center - _pos1;
	
	float dot = v1.dot(v2);
	vec2 proj1 = vec2(((dot / (v1.length2())) * v1.x()),
	                  ((dot / (v1.length2())) * v1.y()));
	vec2 midpt = _pos1 + proj1;
	
	float distToCenter = (midpt - _center).length2();
	if (distToCenter > _radius * _radius) {
		return etk::Pair<vec2,vec2>(vec2(0.0,0.0), vec2(0.0,0.0));
	}
	if (distToCenter == _radius * _radius) {
		return etk::Pair<vec2,vec2>(midpt, midpt);
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
	return etk::Pair<vec2,vec2>(midpt + v1, midpt - v1);
}

etk::Color<float,4> esvg::render::DynamicColorSpecial::getColorRadial(const ivec2& _pos) const {
	float ratio = 0.0f;
	// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object)..
	vec2 intersecX = getIntersect(m_pos1,                   m_axeX,
	                              vec2(_pos.x(), _pos.y()), m_axeY);
	vec2 intersecY = getIntersect(m_pos1,                   m_axeY,
	                              vec2(_pos.x(), _pos.y()), m_axeX);
	vec2 vectorBaseDrawX = intersecX - m_pos1;
	vec2 vectorBaseDrawY = intersecY - m_pos1;
	float baseDrawX = vectorBaseDrawX.length();
	float baseDrawY = vectorBaseDrawY.length();
	// specal case when focal == center (this is faster ...)
	if (m_centerIsFocal == true) {
		ratio = vec2(baseDrawX, baseDrawY).length();
		if (m_baseSize.x()+m_baseSize.y() != 0.0f) {
			if (    m_baseSize.x() != 0.0f
			     && m_baseSize.y() != 0.0f) {
				ratio = vec2(baseDrawX/m_baseSize.x(), baseDrawY/m_baseSize.y()).length();
			} else if (m_baseSize.x() != 0.0f) {
				ratio = baseDrawX/m_baseSize.x();
			} else {
				ratio = baseDrawY/m_baseSize.y();
			}
		} else {
			ratio = 1.0f;
		}
	} else {
		// set the sense of the elements:
		if (m_axeX.dot(vectorBaseDrawX) < 0) {
			baseDrawX *= -1.0f;
		}
		if (m_axeY.dot(vectorBaseDrawY) < 0) {
			baseDrawY *= -1.0f;
		}
		if (m_baseSize.y() != 0.0f) {
			baseDrawY /= m_baseSize.y();
		}
		// normalize to 1.0f
		baseDrawX /= m_baseSize.x();
		if (    m_clipOut == true
		     && baseDrawX <= -1.0f) {
			ratio = 1.0f;
		} else {
			float tmpLength = -m_focalLength/m_baseSize.x();
			vec2 focalCenter = vec2(tmpLength, 0.0f);
			vec2 currentPoint = vec2(baseDrawX, baseDrawY);
			if (focalCenter == currentPoint) {
				ratio = 0.0f;
			} else {
				etk::Pair<vec2,vec2> positions = intersectLineToCircle(focalCenter, currentPoint);
				float lenghtBase = (currentPoint - focalCenter).length();
				float lenghtBorder1 = (positions.first - focalCenter).length();
				float lenghtBorder2 = (positions.second - focalCenter).length();
				ratio = lenghtBase/lenghtBorder1;
			}
		}
	}
	switch(m_spread) {
		case spreadMethod_pad:
			// nothing to do ...
			break;
		case spreadMethod_reflect:
			ratio -= float((int32_t(ratio)>>1)<<1);
			if (ratio > 1.0f) {
				ratio = 2.0f-ratio;
			}
			break;
		case spreadMethod_repeat:
			ratio -= float(int32_t(ratio));
			if (ratio <0.0f) {
				#ifndef __STDCPP_LLVM__
					ratio = 1.0f-etk::abs(ratio);
				#else
					ratio = 1.0f-abs(ratio);
				#endif
			}
			break;
	}
	if (ratio <= m_data[0].first*0.01f) {
		return m_data[0].second;
	}
	if (ratio >= m_data.back().first*0.01f) {
		return m_data.back().second;
	}
	for (size_t iii=1; iii<m_data.size(); ++iii) {
		if (ratio <= m_data[iii].first*0.01f) {
			float localRatio = ratio - m_data[iii-1].first*0.01f;
			localRatio = localRatio / ((m_data[iii].first - m_data[iii-1].first) * 0.01f);
			return etk::Color<float,4>(m_data[iii-1].second.r() * (1.0-localRatio) + m_data[iii].second.r() * localRatio,
			                           m_data[iii-1].second.g() * (1.0-localRatio) + m_data[iii].second.g() * localRatio,
			                           m_data[iii-1].second.b() * (1.0-localRatio) + m_data[iii].second.b() * localRatio,
			                           m_data[iii-1].second.a() * (1.0-localRatio) + m_data[iii].second.a() * localRatio);
		}
	}
	return etk::color::green;
}


void esvg::render::DynamicColorSpecial::generate(esvg::Document* _document) {
	if (_document == nullptr) {
		ESVG_ERROR("Get nullptr input for document");
		return;
	}
	ememory::SharedPtr<esvg::Base> base = _document->getReference(m_colorName);
	if (base == nullptr) {
		ESVG_ERROR("Can not get base : '" << m_colorName << "'");
		return;
	}
	// Now we can know if we use linear or radial gradient ...
	ememory::SharedPtr<esvg::LinearGradient> gradient = ememory::dynamicPointerCast<esvg::LinearGradient>(base);
	if (gradient != nullptr) {
		m_linear = true;
		ESVG_VERBOSE("get for color linear:");
		gradient->display(2);
		m_unit = gradient->m_unit;
		m_spread = gradient->m_spread;
		ESVG_VERBOSE("    viewport = {" << m_viewPort.first << "," << m_viewPort.second << "}");
		vec2 size = m_viewPort.second - m_viewPort.first;
		
		esvg::Dimension dimPos1 = gradient->getPosition1();
		m_pos1 = dimPos1.getPixel(size);
		if (dimPos1.getType() == esvg::distance_pourcent) {
			m_pos1 += m_viewPort.first;
		}
		esvg::Dimension dimPos2 = gradient->getPosition2();
		m_pos2 = dimPos2.getPixel(size);
		if (dimPos2.getType() == esvg::distance_pourcent) {
			m_pos2 += m_viewPort.first;
		}
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		vec2 delta = m_pos2 - m_pos1;
		if (delta.x() < 0.0f) {
			m_axeX = vec2(-1.0f, 0.0f);
		} else {
			m_axeX = vec2(1.0f, 0.0f);
		}
		if (delta.y() < 0.0f) {
			m_axeY = vec2(0.0f, -1.0f);
		} else {
			m_axeY = vec2(0.0f, 1.0f);
		}
		// Move the positions ...
		m_pos1 = m_matrix * m_pos1;
		m_pos2 = m_matrix * m_pos2;
		m_axeX = m_matrix.applyScaleRotation(m_axeX);
		m_axeY = m_matrix.applyScaleRotation(m_axeY);
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		vec2 intersecX = getIntersect(m_pos1, m_axeX,
		                              m_pos2, m_axeY);
		vec2 intersecY = getIntersect(m_pos1, m_axeY,
		                              m_pos2, m_axeX);
		m_baseSize = vec2((m_pos1 - intersecX).length(),
		                  (m_pos1 - intersecY).length());
		// get all the colors
		m_data = gradient->getColors(_document);
	} else {
		m_linear = false;
		ememory::SharedPtr<esvg::RadialGradient> gradient = ememory::dynamicPointerCast<esvg::RadialGradient>(base);
		if (gradient == nullptr) {
			ESVG_ERROR("Can not cast in a linear gradient: '" << m_colorName << "' ==> wrong type");
			return;
		}
		ESVG_VERBOSE("get for color Radial:");
		gradient->display(2);
		m_unit = gradient->m_unit;
		m_spread = gradient->m_spread;
		ESVG_VERBOSE("    viewport = {" << m_viewPort.first << "," << m_viewPort.second << "}");
		vec2 size = m_viewPort.second - m_viewPort.first;
		
		esvg::Dimension dimCenter = gradient->getCenter();
		vec2 center = dimCenter.getPixel(size);
		if (dimCenter.getType() == esvg::distance_pourcent) {
			center += m_viewPort.first;
		}
		esvg::Dimension dimFocal = gradient->getFocal();
		vec2 focal = dimFocal.getPixel(size);
		if (dimFocal.getType() == esvg::distance_pourcent) {
			focal += m_viewPort.first;
		}
		esvg::Dimension1D dimRadius = gradient->getRadius();
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object)..
		if (center == focal) {
			m_centerIsFocal = true;
			m_pos2.setX(dimRadius.getPixel(size.x()));
			m_pos2.setY(dimRadius.getPixel(size.y()));
			m_pos2 += center;
			vec2 delta = center - m_pos2;
			if (delta.x() < 0.0f) {
				m_axeX = vec2(-1.0f, 0.0f);
			} else {
				m_axeX = vec2(1.0f, 0.0f);
			}
			if (delta.y() < 0.0f) {
				m_axeY = vec2(0.0f, -1.0f);
			} else {
				m_axeY = vec2(0.0f, 1.0f);
			}
			m_pos1 = center;
		} else {
			m_centerIsFocal = false;
			m_axeX = (center - focal).safeNormalize();
			m_axeY = vec2(m_axeX.y(), -m_axeX.x());
			
			m_pos2 = m_axeX * dimRadius.getPixel(size.x()) + m_axeY * dimRadius.getPixel(size.y());
			m_pos2 += center;
			m_pos1 = center;
		}
		// Move the positions ...
		m_pos1 = m_matrix * m_pos1;
		center = m_matrix * center;
		m_pos2 = m_matrix * m_pos2;
		m_axeX = m_matrix.applyScaleRotation(m_axeX);
		m_axeY = m_matrix.applyScaleRotation(m_axeY);
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
		vec2 intersecX = getIntersect(m_pos1, m_axeX,
		                              m_pos2, m_axeY);
		vec2 intersecY = getIntersect(m_pos1, m_axeY,
		                              m_pos2, m_axeX);
		m_baseSize = vec2((intersecX - m_pos1).length(),
		                  (intersecY - m_pos1).length());
		if (m_centerIsFocal == false) {
			m_focalLength = (center - m_matrix * focal).length();
			if (m_focalLength >= m_baseSize.x()) {
				ESVG_DEBUG("Change position of the Focal ... ==> set it inside the circle");
				m_focalLength = m_baseSize.x()*0.999998f;
				m_clipOut = true;
			} else {
				m_clipOut = false;
			}
		}
		ESVG_VERBOSE("baseSize=" << m_baseSize << " m_pos1=" << m_pos1 << " dim=" << dimCenter << " m_focal=" << m_focal << " m_pos2=" << m_pos2 << " dim=" << dimRadius);
		// get all the colors
		m_data = gradient->getColors(_document);
	}
}

ememory::SharedPtr<esvg::render::DynamicColor> esvg::render::createColor(etk::Pair<etk::Color<float,4>, etk::String> _color, const mat2x3& _mtx) {
	// Check if need to create a color:
	if (    _color.first.a() == 0x00
	     && _color.second == "") {
	     return nullptr;
	}
	if (_color.second != "") {
		return ememory::makeShared<esvg::render::DynamicColorSpecial>(_color.second, _mtx);
	}
	return ememory::makeShared<esvg::render::DynamicColorUni>(_color.first);
}

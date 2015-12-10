/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/render/DynamicColor.h>
#include <esvg/LinearGradient.h>
#include <esvg/esvg.h>

esvg::render::DynamicColorLinear::DynamicColorLinear(const std::string& _link, const mat2& _mtx) :
  m_colorName(_link),
  m_matrix(_mtx),
  m_viewPort(vec2(9999999999.0,9999999999.0),vec2(-9999999999.0,-9999999999.0)) {
	
}

void esvg::render::DynamicColorLinear::setViewPort(const std::pair<vec2, vec2>& _viewPort) {
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

// TODO : This can optimize ... really slow ...
etk::Color<float,4> esvg::render::DynamicColorLinear::getColor(const ivec2& _pos) {
	if (m_data.size() < 2) {
		return etk::color::purple;
	}
	vec2 vectorBase = m_pos2 - m_pos1;
	vec2 vectorOrtho(vectorBase.y(), -vectorBase.x());
	vec2 intersec = getIntersect(m_pos1,                   vectorBase,
	                             vec2(_pos.x(), _pos.y()), vectorOrtho);
	float baseSize = vectorBase.length();
	float baseDraw = (m_pos1 - intersec).length();
	float ratio = baseDraw / baseSize;
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

void esvg::render::DynamicColorLinear::generate(esvg::Document* _document) {
	if (_document == nullptr) {
		ESVG_ERROR("Get nullptr input for document");
		return;
	}
	std::shared_ptr<esvg::Base> base = _document->getReference(m_colorName);
	if (base == nullptr) {
		ESVG_ERROR("Can not get base : '" << m_colorName << "'");
		return;
	}
	std::shared_ptr<esvg::LinearGradient> gradient = std::dynamic_pointer_cast<esvg::LinearGradient>(base);
	if (gradient == nullptr) {
		ESVG_ERROR("Can not cast in a linear gradient: '" << m_colorName << "' ==> wrong type");
		return;
	}
	ESVG_INFO("get for color linear:");
	gradient->display(2);
	ESVG_INFO("    viewport = {" << m_viewPort.first << "," << m_viewPort.second << "}");
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
	// Move the positions ...
	m_pos1 = m_matrix * m_pos1;
	m_pos2 = m_matrix * m_pos2;
	m_data = gradient->getColors();
}


std::shared_ptr<esvg::render::DynamicColor> esvg::render::createColor(std::pair<etk::Color<float,4>, std::string> _color, const mat2& _mtx) {
	// Check if need to create a color:
	if (    _color.first.a() == 0x00
	     && _color.second == "") {
	     return nullptr;
	}
	if (_color.second != "") {
		return std::make_shared<esvg::render::DynamicColorLinear>(_color.second, _mtx);
	}
	return std::make_shared<esvg::render::DynamicColorUni>(_color.first);
}

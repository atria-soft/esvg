/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/Dimension.h>
#include <esvg/debug.h>

static const float       inchToMillimeter = 1.0f/25.4f;
static const float       footToMillimeter = 1.0f/304.8f;
static const float      meterToMillimeter = 1.0f/1000.0f;
static const float centimeterToMillimeter = 1.0f/10.0f;
static const float  kilometerToMillimeter = 1.0f/1000000.0f;
static const float millimeterToInch = 25.4f;
static const float millimeterToFoot = 304.8f;
static const float millimeterToMeter =1000.0f;
static const float millimeterToCentimeter = 10.0f;
static const float millimeterToKilometer = 1000000.0f;

// 72 px /inch(2.54cm)
static const float basicRatio = 72.0f / 25.4f;

esvg::Dimension::Dimension() :
  m_data(0,0),
  m_type(esvg::distance_pixel) {
	// notinh to do ...
}

esvg::Dimension::Dimension(const vec2& _size, enum esvg::distance _type) :
  m_data(0,0),
  m_type(esvg::distance_pixel) {
	set(_size, _type);
}

void esvg::Dimension::set(std::string _config) {
	m_data.setValue(0,0);
	m_type = esvg::distance_pixel;
	enum distance type = esvg::distance_pixel;
	if (etk::end_with(_config, "%", false) == true) {
		type = esvg::distance_pourcent;
		_config.erase(_config.size()-1, 1);
	} else if (etk::end_with(_config, "px",false) == true) {
		type = esvg::distance_pixel;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "ft",false) == true) {
		type = esvg::distance_foot;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "in",false) == true) {
		type = esvg::distance_inch;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "km",false) == true) {
		type = esvg::distance_kilometer;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "mm",false) == true) {
		type = esvg::distance_millimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "cm",false) == true) {
		type = esvg::distance_centimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "m",false) == true) {
		type = esvg::distance_meter;
		_config.erase(_config.size()-1, 1);
	} else {
		type = esvg::distance_pixel;
		ESVG_VERBOSE("default dimention type for: '" << _config << "' ==> pixel");
		return;
	}
	vec2 tmp = _config;
	set(tmp, type);
	ESVG_VERBOSE(" config dimention : \"" << _config << "\"  == > " << *this );
}

static enum esvg::distance parseType(std::string& _config) {
	enum esvg::distance type = esvg::distance_pixel;
	if (etk::end_with(_config, "%", false) == true) {
		type = esvg::distance_pourcent;
		_config.erase(_config.size()-1, 1);
	} else if (etk::end_with(_config, "px",false) == true) {
		type = esvg::distance_pixel;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "ft",false) == true) {
		type = esvg::distance_foot;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "in",false) == true) {
		type = esvg::distance_inch;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "km",false) == true) {
		type = esvg::distance_kilometer;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "mm",false) == true) {
		type = esvg::distance_millimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "cm",false) == true) {
		type = esvg::distance_centimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "m",false) == true) {
		type = esvg::distance_meter;
		_config.erase(_config.size()-1, 1);
	} else {
		type = esvg::distance_pixel;
		ESVG_VERBOSE("default dimention type for: '" << _config << "' ==> pixel");
	}
	return type;
}


void esvg::Dimension::set(std::string _configX, std::string _configY) {
	m_data.setValue(0,0);
	m_type = esvg::distance_pixel;
	enum distance type = esvg::distance_pixel;
	// First Parse X
	enum distance typeX = parseType(_configX);
	float valueX = etk::string_to_float(_configX);
	// Second Parse Y
	enum distance typeY = parseType(_configY);
	float valueY = etk::string_to_float(_configY);
	// TODO : Check difference ...
	set(vec2(valueX, valueY), typeX);
	ESVG_VERBOSE(" config dimention : '" << _configX << "' '" << _configY << "'  == > " << *this );
}


esvg::Dimension::~Dimension() {
	// nothing to do ...
}

esvg::Dimension::operator std::string() const {
	std::string str;
	str = getValue();
	switch(getType()) {
		case esvg::distance_pourcent:
			str += "%";
			break;
		case esvg::distance_pixel:
			str += "px";
			break;
		case esvg::distance_meter:
			str += "m";
			break;
		case esvg::distance_centimeter:
			str += "cm";
			break;
		case esvg::distance_millimeter:
			str += "mm";
			break;
		case esvg::distance_kilometer:
			str += "km";
			break;
		case esvg::distance_inch:
			str += "in";
			break;
		case esvg::distance_foot:
			str += "ft";
			break;
		case esvg::distance_element:
			str += "em";
			break;
		case esvg::distance_ex:
			str += "ex";
			break;
		case esvg::distance_point:
			str += "pt";
			break;
		case esvg::distance_pc:
			str += "pc";
			break;
	}
	return str;
}

void esvg::Dimension::set(const vec2& _size, enum esvg::distance _type) {
	m_data = _size;
	m_type = _type;
	switch(_type) {
		case esvg::distance_pourcent:
		case esvg::distance_pixel:
			// nothing to do: Supported ...
			break;
		case esvg::distance_meter:
		case esvg::distance_centimeter:
		case esvg::distance_millimeter:
		case esvg::distance_kilometer:
		case esvg::distance_inch:
		case esvg::distance_foot:
		case esvg::distance_element:
		case esvg::distance_ex:
		case esvg::distance_point:
		case esvg::distance_pc:
			ESVG_ERROR("Does not support other than Px and % type of dimention : " << _type << " automaticly convert with {72,72} pixel/inch");
			break;
	}
}

vec2 esvg::Dimension::getPixel(const vec2& _upperSize) const {
	switch(m_type) {
		case esvg::distance_pourcent:
			return vec2(_upperSize.x()*m_data.x()*0.01f, _upperSize.y()*m_data.y()*0.01f);
		case esvg::distance_pixel:
			return m_data;
		case esvg::distance_meter:
			return vec2(m_data.x()*meterToMillimeter*basicRatio, m_data.y()*meterToMillimeter*basicRatio);
		case esvg::distance_centimeter:
			return vec2(m_data.x()*centimeterToMillimeter*basicRatio, m_data.y()*centimeterToMillimeter*basicRatio);
		case esvg::distance_millimeter:
			return vec2(m_data.x()*basicRatio, m_data.y()*basicRatio);
		case esvg::distance_kilometer:
			return vec2(m_data.x()*kilometerToMillimeter*basicRatio, m_data.y()*kilometerToMillimeter*basicRatio);
		case esvg::distance_inch:
			return vec2(m_data.x()*inchToMillimeter*basicRatio, m_data.y()*inchToMillimeter*basicRatio);
		case esvg::distance_foot:
			return vec2(m_data.x()*footToMillimeter*basicRatio, m_data.y()*footToMillimeter*basicRatio);
	}
	return vec2(128.0f, 128.0f);
}

std::ostream& esvg::operator <<(std::ostream& _os, enum esvg::distance _obj) {
	switch(_obj) {
		case esvg::distance_pourcent:
			_os << "%";
			break;
		case esvg::distance_pixel:
			_os << "px";
			break;
		case esvg::distance_meter:
			_os << "m";
			break;
		case esvg::distance_centimeter:
			_os << "cm";
			break;
		case esvg::distance_millimeter:
			_os << "mm";
			break;
		case esvg::distance_kilometer:
			_os << "km";
			break;
		case esvg::distance_inch:
			_os << "in";
			break;
		case esvg::distance_foot:
			_os << "ft";
			break;
		case esvg::distance_element:
			_os << "em";
			break;
		case esvg::distance_ex:
			_os << "ex";
			break;
		case esvg::distance_point:
			_os << "pt";
			break;
		case esvg::distance_pc:
			_os << "pc";
			break;
	}
	return _os;
}

std::ostream& esvg::operator <<(std::ostream& _os, const esvg::Dimension& _obj) {
	_os << _obj.getValue() << _obj.getType();
	return _os;
}

namespace etk {
	template<> std::string to_string<esvg::Dimension>(const esvg::Dimension& _obj) {
		return _obj;
	}
	template<> std::u32string to_u32string<esvg::Dimension>(const esvg::Dimension& _obj) {
		return etk::to_u32string(etk::to_string(_obj));
	}
	template<> bool from_string<esvg::Dimension>(esvg::Dimension& _variableRet, const std::string& _value) {
		_variableRet = esvg::Dimension(_value);
		return true;
	}
	template<> bool from_string<esvg::Dimension>(esvg::Dimension& _variableRet, const std::u32string& _value) {
		return from_string(_variableRet, etk::to_string(_value));
	}
};

esvg::Dimension1D::Dimension1D() :
  m_data(0.0f),
  m_type(esvg::distance_pixel) {
	// notinh to do ...
}

esvg::Dimension1D::Dimension1D(float _size, enum esvg::distance _type) :
  m_data(0.0f),
  m_type(esvg::distance_pixel) {
	set(_size, _type);
}

void esvg::Dimension1D::set(std::string _config) {
	m_data = 0;
	m_type = esvg::distance_pixel;
	enum distance type = esvg::distance_pixel;
	if (etk::end_with(_config, "%", false) == true) {
		type = esvg::distance_pourcent;
		_config.erase(_config.size()-1, 1);
	} else if (etk::end_with(_config, "px",false) == true) {
		type = esvg::distance_pixel;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "ft",false) == true) {
		type = esvg::distance_foot;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "in",false) == true) {
		type = esvg::distance_inch;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "km",false) == true) {
		type = esvg::distance_kilometer;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "mm",false) == true) {
		type = esvg::distance_millimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "cm",false) == true) {
		type = esvg::distance_centimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "m",false) == true) {
		type = esvg::distance_meter;
		_config.erase(_config.size()-1, 1);
	} else {
		type = esvg::distance_pixel;
		ESVG_VERBOSE("default dimention type for: '" << _config << "' ==> pixel");
	}
	float tmp = etk::string_to_float(_config);
	set(tmp, type);
	ESVG_VERBOSE(" config dimention : \"" << _config << "\"  == > " << *this );
}

esvg::Dimension1D::~Dimension1D() {
	// nothing to do ...
}

esvg::Dimension1D::operator std::string() const {
	std::string str;
	str = getValue();
	switch(getType()) {
		case esvg::distance_pourcent:
			str += "%";
			break;
		case esvg::distance_pixel:
			str += "px";
			break;
		case esvg::distance_meter:
			str += "m";
			break;
		case esvg::distance_centimeter:
			str += "cm";
			break;
		case esvg::distance_millimeter:
			str += "mm";
			break;
		case esvg::distance_kilometer:
			str += "km";
			break;
		case esvg::distance_inch:
			str += "in";
			break;
		case esvg::distance_foot:
			str += "ft";
			break;
		case esvg::distance_element:
			str += "em";
			break;
		case esvg::distance_ex:
			str += "ex";
			break;
		case esvg::distance_point:
			str += "pt";
			break;
		case esvg::distance_pc:
			str += "pc";
			break;
	}
	return str;
}

void esvg::Dimension1D::set(float _size, enum esvg::distance _type) {
	m_data = _size;
	m_type = _type;
	switch(_type) {
		case esvg::distance_pourcent:
		case esvg::distance_pixel:
			// nothing to do: Supported ...
			break;
		case esvg::distance_meter:
		case esvg::distance_centimeter:
		case esvg::distance_millimeter:
		case esvg::distance_kilometer:
		case esvg::distance_inch:
		case esvg::distance_foot:
		case esvg::distance_element:
		case esvg::distance_ex:
		case esvg::distance_point:
		case esvg::distance_pc:
			ESVG_ERROR("Does not support other than Px and % type of dimention1D : " << _type << " automaticly convert with {72,72} pixel/inch");
			break;
	}
}

float esvg::Dimension1D::getPixel(float _upperSize) const {
	switch(m_type) {
		case esvg::distance_pourcent:
			return _upperSize*m_data*0.01f;
		case esvg::distance_pixel:
			return m_data;
		case esvg::distance_meter:
			return m_data*meterToMillimeter*basicRatio;
		case esvg::distance_centimeter:
			return m_data*centimeterToMillimeter*basicRatio;
		case esvg::distance_millimeter:
			return m_data*basicRatio;
		case esvg::distance_kilometer:
			return m_data*kilometerToMillimeter*basicRatio;
		case esvg::distance_inch:
			return m_data*inchToMillimeter*basicRatio;
		case esvg::distance_foot:
			return m_data*footToMillimeter*basicRatio;
	}
	return 128.0f;
}

std::ostream& esvg::operator <<(std::ostream& _os, const esvg::Dimension1D& _obj) {
	_os << _obj.getValue() << _obj.getType();
	return _os;
}

namespace etk {
	template<> std::string to_string<esvg::Dimension1D>(const esvg::Dimension1D& _obj) {
		return _obj;
	}
	template<> std::u32string to_u32string<esvg::Dimension1D>(const esvg::Dimension1D& _obj) {
		return etk::to_u32string(etk::to_string(_obj));
	}
	template<> bool from_string<esvg::Dimension1D>(esvg::Dimension1D& _variableRet, const std::string& _value) {
		_variableRet = esvg::Dimension1D(_value);
		return true;
	}
	template<> bool from_string<esvg::Dimension1D>(esvg::Dimension1D& _variableRet, const std::u32string& _value) {
		return from_string(_variableRet, etk::to_string(_value));
	}
};





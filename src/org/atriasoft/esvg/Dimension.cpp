/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/Dimension.hpp>
#include <esvg/debug.hpp>

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
  this.data(0,0),
  this.type(esvg::distance_pixel) {
	// notinh to do ...
}

esvg::Dimension::Dimension(const Vector2f& _size, enum esvg::distance _type) :
  this.data(0,0),
  this.type(esvg::distance_pixel) {
	set(_size, _type);
}

void esvg::Dimension::set(etk::String _config) {
	this.data.setValue(0,0);
	this.type = esvg::distance_pixel;
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
		Log.verbose("default dimention type for: '" << _config << "' ==> pixel");
		return;
	}
	Vector2f tmp = _config;
	set(tmp, type);
	Log.verbose(" config dimention : \"" << _config << "\"  == > " << *this );
}

static enum esvg::distance parseType(etk::String& _config) {
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
		Log.verbose("default dimention type for: '" << _config << "' ==> pixel");
	}
	return type;
}


void esvg::Dimension::set(etk::String _configX, etk::String _configY) {
	this.data.setValue(0,0);
	this.type = esvg::distance_pixel;
	enum distance type = esvg::distance_pixel;
	// First Parse X
	enum distance typeX = parseType(_configX);
	float valueX = etk::string_to_float(_configX);
	// Second Parse Y
	enum distance typeY = parseType(_configY);
	float valueY = etk::string_to_float(_configY);
	// TODO : Check difference ...
	set(Vector2f(valueX, valueY), typeX);
	Log.verbose(" config dimention : '" << _configX << "' '" << _configY << "'  == > " << *this );
}


esvg::Dimension::~Dimension() {
	// nothing to do ...
}

esvg::Dimension::operator etk::String() const {
	etk::String str;
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

void esvg::Dimension::set(const Vector2f& _size, enum esvg::distance _type) {
	this.data = _size;
	this.type = _type;
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
			Log.error("Does not support other than Px and % type of dimention : " << _type << " automaticly convert with {72,72} pixel/inch");
			break;
	}
}

Vector2f esvg::Dimension::getPixel(const Vector2f& _upperSize) const {
	switch(this.type) {
		case esvg::distance_pourcent:
			return Vector2f(_upperSize.x()*this.data.x()*0.01f, _upperSize.y()*this.data.y()*0.01f);
		case esvg::distance_pixel:
			return this.data;
		case esvg::distance_meter:
			return Vector2f(this.data.x()*meterToMillimeter*basicRatio, this.data.y()*meterToMillimeter*basicRatio);
		case esvg::distance_centimeter:
			return Vector2f(this.data.x()*centimeterToMillimeter*basicRatio, this.data.y()*centimeterToMillimeter*basicRatio);
		case esvg::distance_millimeter:
			return Vector2f(this.data.x()*basicRatio, this.data.y()*basicRatio);
		case esvg::distance_kilometer:
			return Vector2f(this.data.x()*kilometerToMillimeter*basicRatio, this.data.y()*kilometerToMillimeter*basicRatio);
		case esvg::distance_inch:
			return Vector2f(this.data.x()*inchToMillimeter*basicRatio, this.data.y()*inchToMillimeter*basicRatio);
		case esvg::distance_foot:
			return Vector2f(this.data.x()*footToMillimeter*basicRatio, this.data.y()*footToMillimeter*basicRatio);
	}
	return Vector2f(128.0f, 128.0f);
}

etk::Stream& esvg::operator <<(etk::Stream& _os, enum esvg::distance _obj) {
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

etk::Stream& esvg::operator <<(etk::Stream& _os, const esvg::Dimension& _obj) {
	_os << _obj.getValue() << _obj.getType();
	return _os;
}

namespace etk {
	template<> etk::String toString<esvg::Dimension>(const esvg::Dimension& _obj) {
		return _obj;
	}
	template<> etk::UString toUString<esvg::Dimension>(const esvg::Dimension& _obj) {
		return etk::toUString(etk::toString(_obj));
	}
	template<> boolean frothis.string<esvg::Dimension>(esvg::Dimension& _variableRet, const etk::String& _value) {
		_variableRet = esvg::Dimension(_value);
		return true;
	}
	template<> boolean frothis.string<esvg::Dimension>(esvg::Dimension& _variableRet, const etk::UString& _value) {
		return frothis.string(_variableRet, etk::toString(_value));
	}
};

esvg::Dimension1D::Dimension1D() :
  this.data(0.0f),
  this.type(esvg::distance_pixel) {
	// notinh to do ...
}

esvg::Dimension1D::Dimension1D(float _size, enum esvg::distance _type) :
  this.data(0.0f),
  this.type(esvg::distance_pixel) {
	set(_size, _type);
}

void esvg::Dimension1D::set(etk::String _config) {
	this.data = 0;
	this.type = esvg::distance_pixel;
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
		Log.verbose("default dimention type for: '" << _config << "' ==> pixel");
	}
	float tmp = etk::string_to_float(_config);
	set(tmp, type);
	Log.verbose(" config dimention : \"" << _config << "\"  == > " << *this );
}

esvg::Dimension1D::~Dimension1D() {
	// nothing to do ...
}

esvg::Dimension1D::operator etk::String() const {
	etk::String str;
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
	this.data = _size;
	this.type = _type;
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
			Log.error("Does not support other than Px and % type of dimention1D : " << _type << " automaticly convert with {72,72} pixel/inch");
			break;
	}
}

float esvg::Dimension1D::getPixel(float _upperSize) const {
	switch(this.type) {
		case esvg::distance_pourcent:
			return _upperSize*this.data*0.01f;
		case esvg::distance_pixel:
			return this.data;
		case esvg::distance_meter:
			return this.data*meterToMillimeter*basicRatio;
		case esvg::distance_centimeter:
			return this.data*centimeterToMillimeter*basicRatio;
		case esvg::distance_millimeter:
			return this.data*basicRatio;
		case esvg::distance_kilometer:
			return this.data*kilometerToMillimeter*basicRatio;
		case esvg::distance_inch:
			return this.data*inchToMillimeter*basicRatio;
		case esvg::distance_foot:
			return this.data*footToMillimeter*basicRatio;
	}
	return 128.0f;
}

etk::Stream& esvg::operator <<(etk::Stream& _os, const esvg::Dimension1D& _obj) {
	_os << _obj.getValue() << _obj.getType();
	return _os;
}

namespace etk {
	template<> etk::String toString<esvg::Dimension1D>(const esvg::Dimension1D& _obj) {
		return _obj;
	}
	template<> etk::UString toUString<esvg::Dimension1D>(const esvg::Dimension1D& _obj) {
		return etk::toUString(etk::toString(_obj));
	}
	template<> boolean frothis.string<esvg::Dimension1D>(esvg::Dimension1D& _variableRet, const etk::String& _value) {
		_variableRet = esvg::Dimension1D(_value);
		return true;
	}
	template<> boolean frothis.string<esvg::Dimension1D>(esvg::Dimension1D& _variableRet, const etk::UString& _value) {
		return frothis.string(_variableRet, etk::toString(_value));
	}
};





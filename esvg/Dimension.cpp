/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gale/Dimension.h>
#include <gale/debug.h>

#undef __class__
#define __class__	"Dimension"

// TODO : set this in a super class acced in a statin fuction...
// ratio in milimeter :
static bool isInit = false;
static vec2 ratio(9999999,888888);
static vec2 invRatio(1,1);
static gale::Dimension windowsSize(vec2(9999999,888888), gale::Dimension::Pixel);

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


void gale::Dimension::init() {
	if (true == isInit) {
		return;
	}
	gale::Dimension conversion(vec2(72,72), gale::Dimension::Inch);
	ratio = conversion.getMillimeter();
	invRatio.setValue(1.0f/ratio.x(),1.0f/ratio.y());
	windowsSize.set(vec2(200,200), gale::Dimension::Pixel);
	isInit = true;
}

void gale::Dimension::unInit() {
	isInit = false;
	ratio.setValue(9999999,888888);
	invRatio.setValue(1.0f/ratio.x(),1.0f/ratio.y());
	windowsSize.set(vec2(9999999,88888), gale::Dimension::Pixel);
}

void gale::Dimension::setPixelRatio(const vec2& _ratio, enum gale::Dimension::distance _type) {
	gale::Dimension::init();
	GALE_INFO("Set a new screen ratio for the screen : ratio=" << _ratio << " type=" << _type);
	gale::Dimension conversion(_ratio, _type);
	GALE_INFO("     == > " << conversion);
	ratio = conversion.getMillimeter();
	invRatio.setValue(1.0f/ratio.x(),1.0f/ratio.y());
	GALE_INFO("Set a new screen ratio for the screen : ratioMm=" << ratio);
}

void gale::Dimension::setPixelWindowsSize(const vec2& _size) {
	windowsSize = _size;
	GALE_VERBOSE("Set a new Windows property size " << windowsSize << "px");
}

vec2 gale::Dimension::getWindowsSize(enum gale::Dimension::distance _type) {
	return windowsSize.get(_type);
}

float gale::Dimension::getWindowsDiag(enum gale::Dimension::distance _type) {
	vec2 size = gale::Dimension::getWindowsSize(_type);
	return size.length();
}

gale::Dimension::Dimension() :
  m_data(0,0),
  m_type(gale::Dimension::Pixel) {
	// notinh to do ...
}

gale::Dimension::Dimension(const vec2& _size, enum gale::Dimension::distance _type) :
  m_data(0,0),
  m_type(gale::Dimension::Pixel) {
	set(_size, _type);
}

void gale::Dimension::set(std::string _config) {
	m_data.setValue(0,0);
	m_type = gale::Dimension::Pixel;
	enum distance type = gale::Dimension::Pixel;
	if (etk::end_with(_config, "%", false) == true) {
		type = gale::Dimension::Pourcent;
		_config.erase(_config.size()-1, 1);
	} else if (etk::end_with(_config, "px",false) == true) {
		type = gale::Dimension::Pixel;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "ft",false) == true) {
		type = gale::Dimension::foot;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "in",false) == true) {
		type = gale::Dimension::Inch;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "km",false) == true) {
		type = gale::Dimension::Kilometer;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "mm",false) == true) {
		type = gale::Dimension::Millimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "cm",false) == true) {
		type = gale::Dimension::Centimeter;
		_config.erase(_config.size()-2, 2);
	} else if (etk::end_with(_config, "m",false) == true) {
		type = gale::Dimension::Meter;
		_config.erase(_config.size()-1, 1);
	} else {
		GALE_CRITICAL("Can not parse dimention : \"" << _config << "\"");
		return;
	}
	vec2 tmp = _config;
	set(tmp, type);
	GALE_VERBOSE(" config dimention : \"" << _config << "\"  == > " << *this );
}

gale::Dimension::~Dimension() {
	// nothing to do ...
}

gale::Dimension::operator std::string() const {
	std::string str;
	str = get(getType());
	
	switch(getType()) {
		case gale::Dimension::Pourcent:
			str += "%";
			break;
		case gale::Dimension::Pixel:
			str += "px";
			break;
		case gale::Dimension::Meter:
			str += "m";
			break;
		case gale::Dimension::Centimeter:
			str += "cm";
			break;
		case gale::Dimension::Millimeter:
			str += "mm";
			break;
		case gale::Dimension::Kilometer:
			str += "km";
			break;
		case gale::Dimension::Inch:
			str += "in";
			break;
		case gale::Dimension::foot:
			str += "ft";
			break;
	}
	return str;
}

vec2 gale::Dimension::get(enum gale::Dimension::distance _type) const {
	switch(_type) {
		case gale::Dimension::Pourcent:
			return getPourcent();
		case gale::Dimension::Pixel:
			return getPixel();
		case gale::Dimension::Meter:
			return getMeter();
		case gale::Dimension::Centimeter:
			return getCentimeter();
		case gale::Dimension::Millimeter:
			return getMillimeter();
		case gale::Dimension::Kilometer:
			return getKilometer();
		case gale::Dimension::Inch:
			return getInch();
		case gale::Dimension::foot:
			return getFoot();
	}
	return vec2(0,0);
}

void gale::Dimension::set(const vec2& _size, enum gale::Dimension::distance _type) {
	// set min max on input to limit error : 
	vec2 size(std::avg(0.0f,_size.x(),9999999.0f),
	          std::avg(0.0f,_size.y(),9999999.0f));
	switch(_type) {
		case gale::Dimension::Pourcent: {
			vec2 size2(std::avg(0.0f,_size.x(),100.0f),
			           std::avg(0.0f,_size.y(),100.0f));
			m_data = vec2(size2.x()*0.01f, size2.y()*0.01f);
			//GALE_VERBOSE("Set % : " << size2 << "  == > " << m_data);
			break;
		}
		case gale::Dimension::Pixel:
			m_data = size;
			break;
		case gale::Dimension::Meter:
			m_data = vec2(size.x()*meterToMillimeter*ratio.x(), size.y()*meterToMillimeter*ratio.y());
			break;
		case gale::Dimension::Centimeter:
			m_data = vec2(size.x()*centimeterToMillimeter*ratio.x(), size.y()*centimeterToMillimeter*ratio.y());
			break;
		case gale::Dimension::Millimeter:
			m_data = vec2(size.x()*ratio.x(), size.y()*ratio.y());
			break;
		case gale::Dimension::Kilometer:
			m_data = vec2(size.x()*kilometerToMillimeter*ratio.x(), size.y()*kilometerToMillimeter*ratio.y());
			break;
		case gale::Dimension::Inch:
			m_data = vec2(size.x()*inchToMillimeter*ratio.x(), size.y()*inchToMillimeter*ratio.y());
			break;
		case gale::Dimension::foot:
			m_data = vec2(size.x()*footToMillimeter*ratio.x(), size.y()*footToMillimeter*ratio.y());
			break;
	}
	m_type = _type;
}

vec2 gale::Dimension::getPixel() const {
	if (m_type!=gale::Dimension::Pourcent) {
		return m_data;
	} else {
		vec2 windDim = windowsSize.getPixel();
		vec2 res = vec2(windDim.x()*m_data.x(), windDim.y()*m_data.y());
		//GALE_DEBUG("Get % : " << m_data << " / " << windDim << " == > " << res);
		return res;
	}
}

vec2 gale::Dimension::getPourcent() const {
	if (m_type!=gale::Dimension::Pourcent) {
		vec2 windDim = windowsSize.getPixel();
		//GALE_DEBUG(" windows dimention : " /*<< windowsSize*/ << "  == > " << windDim << "px"); // ==> infinite loop ...
		//printf(" windows dimention : %f,%f", windDim.x(),windDim.y());
		//printf(" data : %f,%f", m_data.x(),m_data.y());
		return vec2((m_data.x()/windDim.x())*100.0f, (m_data.y()/windDim.y())*100.0f);
	}
	return vec2(m_data.x()*100.0f, m_data.y()*100.0f);;
}

vec2 gale::Dimension::getMeter() const {
	return gale::Dimension::getMillimeter()*millimeterToMeter;
}

vec2 gale::Dimension::getCentimeter() const {
	return gale::Dimension::getMillimeter()*millimeterToCentimeter;
}

vec2 gale::Dimension::getMillimeter() const {
	return gale::Dimension::getPixel()*invRatio;
}

vec2 gale::Dimension::getKilometer() const {
	return gale::Dimension::getMillimeter()*millimeterToKilometer;
}

vec2 gale::Dimension::getInch() const {
	return gale::Dimension::getMillimeter()*millimeterToInch;
}

vec2 gale::Dimension::getFoot() const {
	return gale::Dimension::getMillimeter()*millimeterToFoot;
}

std::ostream& gale::operator <<(std::ostream& _os, enum gale::Dimension::distance _obj) {
	switch(_obj) {
		case gale::Dimension::Pourcent:
			_os << "%";
			break;
		case gale::Dimension::Pixel:
			_os << "px";
			break;
		case gale::Dimension::Meter:
			_os << "m";
			break;
		case gale::Dimension::Centimeter:
			_os << "cm";
			break;
		case gale::Dimension::Millimeter:
			_os << "mm";
			break;
		case gale::Dimension::Kilometer:
			_os << "km";
			break;
		case gale::Dimension::Inch:
			_os << "in";
			break;
		case gale::Dimension::foot:
			_os << "ft";
			break;
	}
	return _os;
}

std::ostream& gale::operator <<(std::ostream& _os, const gale::Dimension& _obj) {
	_os << _obj.get(_obj.getType()) << _obj.getType();
	return _os;
}

namespace etk {
	template<> std::string to_string<gale::Dimension>(const gale::Dimension& _obj) {
		return _obj;
	}
	template<> std::u32string to_u32string<gale::Dimension>(const gale::Dimension& _obj) {
		return etk::to_u32string(etk::to_string(_obj));
	}
	template<> bool from_string<gale::Dimension>(gale::Dimension& _variableRet, const std::string& _value) {
		_variableRet = gale::Dimension(_value);
		return true;
	}
	template<> bool from_string<gale::Dimension>(gale::Dimension& _variableRet, const std::u32string& _value) {
		return from_string(_variableRet, etk::to_string(_value));
	}
};

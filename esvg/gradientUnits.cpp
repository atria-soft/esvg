/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/gradientUnits.h>
#include <esvg/debug.h>

static const char* values[] = {
	"userSpaceOnUse",
	"objectBoundingBox"
};

std::ostream& esvg::operator <<(std::ostream& _os, enum esvg::gradientUnits _obj) {
	_os << values[_obj];
	return _os;
}


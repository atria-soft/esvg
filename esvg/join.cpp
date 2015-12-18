/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/join.h>
#include <esvg/debug.h>

static const char* values[] = {
	"miter",
	"round",
	"bevel"
};

std::ostream& esvg::operator <<(std::ostream& _os, enum esvg::join _obj) {
	_os << values[_obj];
	return _os;
}


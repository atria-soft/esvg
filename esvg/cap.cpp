/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/cap.hpp>
#include <esvg/debug.hpp>

static const char* values[] = {
	"butt",
	"round",
	"square"
};

std::ostream& esvg::operator <<(std::ostream& _os, enum esvg::cap _obj) {
	_os << values[_obj];
	return _os;
}


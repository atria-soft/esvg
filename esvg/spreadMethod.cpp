/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/spreadMethod.hpp>
#include <esvg/debug.hpp>

static const char* values[] = {
	"pad",
	"reflect",
	"repeat"
};

std::ostream& esvg::operator <<(std::ostream& _os, enum esvg::spreadMethod _obj) {
	_os << values[_obj];
	return _os;
}


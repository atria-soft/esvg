/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/gradientUnits.hpp>
#include <esvg/debug.hpp>

static const char* values[] = {
	"userSpaceOnUse",
	"objectBoundingBox"
};

etk::Stream& esvg::operator <<(etk::Stream& _os, enum esvg::gradientUnits _obj) {
	_os << values[_obj];
	return _os;
}


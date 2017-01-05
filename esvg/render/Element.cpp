/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

std::ostream& esvg::operator <<(std::ostream& _os, enum esvg::render::path _obj) {
	switch (_obj) {
		case esvg::render::path_stop:
			_os << "path_stop";
			break;
		case esvg::render::path_close:
			_os << "path_close";
			break;
		case esvg::render::path_moveTo:
			_os << "path_moveTo";
			break;
		case esvg::render::path_lineTo:
			_os << "path_lineTo";
			break;
		case esvg::render::path_lineToH:
			_os << "path_lineToH";
			break;
		case esvg::render::path_lineToV:
			_os << "path_lineToV";
			break;
		case esvg::render::path_curveTo:
			_os << "path_curveTo";
			break;
		case esvg::render::path_smoothCurveTo:
			_os << "path_smoothCurveTo";
			break;
		case esvg::render::path_bezierCurveTo:
			_os << "path_bezierCurveTo";
			break;
		case esvg::render::path_bezierSmoothCurveTo:
			_os << "path_bezierSmoothCurveTo";
			break;
		case esvg::render::path_elliptic:
			_os << "path_elliptic";
			break;
		default:
			_os << "????";
			break;
	};
	return _os;
}
std::ostream& esvg::operator <<(std::ostream& _os, const esvg::render::Element& _obj) {
	_os << _obj.getType();
	_os << ": rel=" << etk::to_string(_obj.getRelative()) << " ";
	_os << _obj.display();
	return _os;
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Stream.hpp>

namespace esvg {
	enum spreadMethod {
		spreadMethod_pad,
		spreadMethod_reflect,
		spreadMethod_repeat
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	etk::Stream& operator <<(etk::Stream& _os, enum esvg::spreadMethod _obj);
}



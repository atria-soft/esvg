/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_SPREAD_METHOD_H__
#define __ESVG_SPREAD_METHOD_H__

#include <etk/types.h>

namespace esvg {
	enum spreadMethod {
		spreadMethod_pad,
		spreadMethod_reflect,
		spreadMethod_repeat
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, enum esvg::spreadMethod _obj);
}

#endif


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_GRADIENT_UNIT_H__
#define __ESVG_GRADIENT_UNIT_H__

#include <etk/types.h>

namespace esvg {
	enum gradientUnits {
		gradientUnits_userSpaceOnUse,
		gradientUnits_objectBoundingBox
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, enum esvg::gradientUnits _obj);
}

#endif


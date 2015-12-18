/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_JOIN_H__
#define __ESVG_JOIN_H__

#include <etk/types.h>

namespace esvg {
	enum join {
		join_miter,
		join_round,
		join_bevel
	};
	/**
	 * @brief Debug operator To display the curent element in a Human redeable information
	 */
	std::ostream& operator <<(std::ostream& _os, enum esvg::join _obj);
}

#endif


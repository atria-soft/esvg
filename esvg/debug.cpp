/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>

int32_t esvg::getLogId() {
	static int32_t g_val = elog::registerInstance("esvg");
	return g_val;
}


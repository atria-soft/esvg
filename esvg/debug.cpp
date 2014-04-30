/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <esvg/debug.h>

int32_t esvg::getLogId(void) {
	static int32_t g_val = etk::log::registerInstance("esvg");
	return g_val;
}


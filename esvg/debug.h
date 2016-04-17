/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <elog/log.h>

namespace esvg {
	int32_t getLogId();
};
#define ESVG_BASE(info,data)     ELOG_BASE(esvg::getLogId(),info,data)

#define ESVG_PRINT(data)         ESVG_BASE(-1, data)
#define ESVG_CRITICAL(data)      ESVG_BASE(1, data)
#define ESVG_ERROR(data)         ESVG_BASE(2, data)
#define ESVG_WARNING(data)       ESVG_BASE(3, data)
#ifdef DEBUG
	#define ESVG_INFO(data)          ESVG_BASE(4, data)
	#define ESVG_DEBUG(data)         ESVG_BASE(5, data)
	#define ESVG_VERBOSE(data)       ESVG_BASE(6, data)
	#define ESVG_TODO(data)          ESVG_BASE(4, "TODO : " << data)
#else
	#define ESVG_INFO(data)          do { } while(false)
	#define ESVG_DEBUG(data)         do { } while(false)
	#define ESVG_VERBOSE(data)       do { } while(false)
	#define ESVG_TODO(data)          do { } while(false)
#endif

#define ESVG_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			SVG_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)



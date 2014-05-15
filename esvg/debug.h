/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_DEBUG_H__
#define __ESVG_DEBUG_H__

#include <etk/log.h>

namespace esvg {
	int32_t getLogId();
};
// TODO : Review this problem of multiple intanciation of "std::stringbuf sb"
#define SVG_BASE(info,data) \
	do { \
		if (info <= etk::log::getLevel(esvg::getLogId())) { \
			std::stringbuf sb; \
			std::ostream tmpStream(&sb); \
			tmpStream << data; \
			etk::log::logStream(esvg::getLogId(), info, __LINE__, __class__, __func__, tmpStream); \
		} \
	} while(0)

#define SVG_CRITICAL(data)      SVG_BASE(1, data)
#define SVG_ERROR(data)         SVG_BASE(2, data)
#define SVG_WARNING(data)       SVG_BASE(3, data)
#ifdef DEBUG
	#define SVG_INFO(data)          SVG_BASE(4, data)
	#define SVG_DEBUG(data)         SVG_BASE(5, data)
	#define SVG_VERBOSE(data)       SVG_BASE(6, data)
	#define SVG_TODO(data)          SVG_BASE(4, "TODO : " << data)
#else
	#define SVG_INFO(data)          do { } while(false)
	#define SVG_DEBUG(data)         do { } while(false)
	#define SVG_VERBOSE(data)       do { } while(false)
	#define SVG_TODO(data)          do { } while(false)
#endif

#define SVG_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			SVG_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

#endif


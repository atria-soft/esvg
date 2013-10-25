/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_DEBUG_H__
#define __ESVG_DEBUG_H__

#include <etk/types.h>
#include <etk/debugGeneric.h>

extern const char * esvgLibName;

#define SVG_CRITICAL(data)			ETK_CRITICAL(esvgLibName, data)
#define SVG_WARNING(data)			ETK_WARNING(esvgLibName, data)
#define SVG_ERROR(data)				ETK_ERROR(esvgLibName, data)
#define SVG_INFO(data)				ETK_INFO(esvgLibName, data)
#define SVG_DEBUG(data)				ETK_DEBUG(esvgLibName, data)
#define SVG_VERBOSE(data)			ETK_VERBOSE(esvgLibName, data)
#define SVG_ASSERT(cond, data)		ETK_ASSERT(esvgLibName, cond, data)
#define SVG_CHECK_INOUT(cond)		ETK_CHECK_INOUT(esvgLibName, cond)
#define SVG_TODO(cond)				ETK_TODO(esvgLibName, cond)

#endif


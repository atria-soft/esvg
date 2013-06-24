/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __PARSER_SVG_DEBUG_H__
#define __PARSER_SVG_DEBUG_H__

#include <etk/types.h>
#include <etk/Debug.h>

extern const char * parserSVGLibName;

#define SVG_CRITICAL(data)			ETK_CRITICAL(parserSVGLibName, data)
#define SVG_WARNING(data)			ETK_WARNING(parserSVGLibName, data)
#define SVG_ERROR(data)				ETK_ERROR(parserSVGLibName, data)
#define SVG_INFO(data)				ETK_INFO(parserSVGLibName, data)
#define SVG_DEBUG(data)				ETK_DEBUG(parserSVGLibName, data)
#define SVG_VERBOSE(data)			ETK_VERBOSE(parserSVGLibName, data)
#define SVG_ASSERT(cond, data)		ETK_ASSERT(parserSVGLibName, cond, data)
#define SVG_CHECK_INOUT(cond)		ETK_CHECK_INOUT(parserSVGLibName, cond)
#define SVG_TODO(cond)				ETK_TODO(parserSVGLibName, cond)

#endif


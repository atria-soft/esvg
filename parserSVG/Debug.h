/**
 *******************************************************************************
 * @file tinySVG/Debug.h
 * @brief SVG : log wrapper (header)
 * @author Edouard DUPIN
 * @date 18/03/2012
 * @par Project
 * parserSVG
 *
 * @par Copyright
 * Copyright 2011 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */

#ifndef __PARSER_SVG_DEBUG_H__
#define __PARSER_SVG_DEBUG_H__

#include <etk/Types.h>
#include <etk/Debug.h>

extern const char * parserSVGLibName;

#define SVG_CRITICAL(data)         ETK_CRITICAL(parserSVGLibName, data)
// General 
#if SVG_DEBUG_LEVEL > 0
#	define SVG_WARNING(data)       ETK_WARNING(parserSVGLibName, data)
#	define SVG_ERROR(data)         ETK_ERROR(parserSVGLibName, data)
#else
#	define SVG_WARNING(data)       do {}while(0)
#	define SVG_ERROR(data)         do {}while(0)
#endif

#if SVG_DEBUG_LEVEL > 1
#	define SVG_INFO(data)          ETK_INFO(parserSVGLibName, data)
#else
#	define SVG_INFO(data)          do {}while(0)
#endif

#if SVG_DEBUG_LEVEL > 2
#	define SVG_DEBUG(data)         ETK_DEBUG(parserSVGLibName, data)
#else
#	define SVG_DEBUG(data)         do {}while(0)
#endif

#if SVG_DEBUG_LEVEL > 3
#	define SVG_VERBOSE(data)         ETK_VERBOSE(parserSVGLibName, data)
#else
#	define SVG_VERBOSE(data)         do {}while(0)
#endif

#define SVG_TODO(data)             SVG_WARNING("TODO : " << data)

#define SVG_ASSERT(cond, data)     ETK_ASSERT(parserSVGLibName, cond, data)

#if SVG_DEBUG_LEVEL > 1
#	define SVG_CHECK_INOUT(cond)   ETK_CHECK_INOUT_ASSERT(parserSVGLibName, cond)
#elif SVG_DEBUG_LEVEL > 0
#	define SVG_CHECK_INOUT(cond)   ETK_CHECK_INOUT_WARNING(parserSVGLibName, cond)
#else
#	define SVG_CHECK_INOUT(cond)   do { } while (0)
#endif


#endif


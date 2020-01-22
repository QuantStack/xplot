/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_CONFIG_HPP
#define XPLOT_CONFIG_HPP

#include <string>

// Visual C++ declspec macros
#ifdef _WIN32
    #ifdef XPLOT_EXPORTS
        #define XPLOT_API __declspec(dllexport)
    #else
        #define XPLOT_API __declspec(dllimport)
    #endif
#else
    #define XPLOT_API
#endif

// Project version
#define XPLOT_VERSION_MAJOR 0
#define XPLOT_VERSION_MINOR 15
#define XPLOT_VERSION_PATCH 0

// Binary version
#define XPLOT_BINARY_CURRENT 1
#define XPLOT_BINARY_REVISION 0
#define XPLOT_BINARY_AGE 1

// Semver requirement for bqplot
#define XBQPLOT_VERSION_MAJOR 0
#define XBQPLOT_VERSION_MINOR 4
#define XBQPLOT_VERSION_PATCH 3

// Composing the version strings from major, minor and patch
#define XPLOT_CONCATENATE(A, B) XPLOT_CONCATENATE_IMPL(A, B)
#define XPLOT_CONCATENATE_IMPL(A, B) A##B
#define XPLOT_STRINGIFY(a) XPLOT_STRINGIFY_IMPL(a)
#define XPLOT_STRINGIFY_IMPL(a) #a

#define XBQPLOT_VERSION XPLOT_STRINGIFY(XPLOT_CONCATENATE(XBQPLOT_VERSION_MAJOR,   \
                    XPLOT_CONCATENATE(.,XPLOT_CONCATENATE(XBQPLOT_VERSION_MINOR,   \
                                      XPLOT_CONCATENATE(.,XBQPLOT_VERSION_PATCH)))))

inline std::string bqplot_semver()
{
    return std::string("^") + XBQPLOT_VERSION;
}

#ifdef __CLING__
#include "xplot_config_cling.hpp"
#endif

#endif

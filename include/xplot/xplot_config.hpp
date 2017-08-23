/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_CONFIG_HPP
#define XPLOT_CONFIG_HPP

#define XPLOT_VERSION_MAJOR 0
#define XPLOT_VERSION_MINOR 1
#define XPLOT_VERSION_PATCH 0

#ifdef _WIN32
    #ifdef XPLOT_EXPORTS
        #define XPLOT_API __declspec(dllexport)
    #else
        #define XPLOT_API __declspec(dllimport)
    #endif
#else
    #define XPLOT_API
#endif

#endif

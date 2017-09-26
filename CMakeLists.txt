############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille                        #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.1)
project(xplot)

set(XPLOT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XPLOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Versionning
# ===========

file(STRINGS "${XPLOT_INCLUDE_DIR}/xplot/xplot_config.hpp" xplot_version_defines
     REGEX "#define XPLOT_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xplot_version_defines})
    if(ver MATCHES "#define XPLOT_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XWIDGETS_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION 
    ${XPLOT_VERSION_MAJOR}.${XPLOT_VERSION_MINOR}.${XPLOT_VERSION_PATCH})
message(STATUS "xplot v${${PROJECT_NAME}_VERSION}")

# Compilation flags
# =================

include(CheckCXXCompilerFlag)

string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter -Wextra -Wreorder")
    if (DISABLE_ARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=generic")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()

    CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

    if (HAS_CPP11_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- xeux requires c++14 support!")
    endif()

    # Enable link time optimization and set the default symbol
    # visibility to hidden (very important to obtain small binaries)
    if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        # Check for Link Time Optimization support
        # (GCC/Clang)
        CHECK_CXX_COMPILER_FLAG("-flto" HAS_LTO_FLAG)
        if (HAS_LTO_FLAG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
        endif()

        # Intel equivalent to LTO is called IPO
        if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
            CHECK_CXX_COMPILER_FLAG("-ipo" HAS_IPO_FLAG)
            if (HAS_IPO_FLAG)
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ipo")
            endif()
        endif()
    endif()
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

if(MSVC)
    add_definitions(-DNOMINMAX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /wd4996")
    # Allows to compile in debug without requiring each dependencies to
    # be compiled in debug
    if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
        message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
endif()

# Dependencies
# ============

find_package(xeus REQUIRED)
include_directories(${xeus_INCLUDE_DIRS})

find_package(xproperty REQUIRED)
include_directories(${xproperty_INCLUDE_DIRS})

find_package(xwidgets REQUIRED)
include_directories(${xwidgets_INCLUDE_DIRS})

set(XPLOT_DEPENDENCIES ${xeus_LIBRARY})

# Source files
# ============

include_directories(${XPLOT_INCLUDE_DIR}/xplot)

set(MAPFILESPEC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/xplot/map_data)
set(XPLOT_MAPFILESPEC_INSTALL_DIR "share/jupyter" CACHE STRING "install path for kernel specs")

install(DIRECTORY ${MAPFILESPEC_DIR}
        DESTINATION ${XPLOT_MAPFILESPEC_INSTALL_DIR})

set(MAPFILE_DIR "\"${CMAKE_INSTALL_PREFIX}/${XPLOT_MAPFILESPEC_INSTALL_DIR}/map_data/\"")

configure_file (
    "${XPLOT_INCLUDE_DIR}/xplot/xmaps_config.hpp.in"
    "${XPLOT_INCLUDE_DIR}/xplot/xmaps_config.hpp"
)

include_directories(${PROJECT_BINARY_DIR})

set(XPLOT_HEADERS
    ${XPLOT_INCLUDE_DIR}/xplot/xaxes.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xboxed_container.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xfigure.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xmarks.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xplot.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xplot_config.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xscales.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xmaps_config.hpp
    )

# # Output
# # ======
# 
# set(XPLOT_TARGET xplot)
# add_library(${XPLOT_TARGET} SHARED ${XPLOT_SOURCES} ${XPLOT_HEADERS})
# target_link_libraries(${XPLOT_TARGET} ${XPLOT_DEPENDENCIES})
# set_target_properties(${XPLOT_TARGET} PROPERTIES
#                       PUBLIC_HEADER "${XPLOT_HEADERS}"
#                       COMPILE_DEFINITIONS "XPLOT_EXPORTS"
#                       PREFIX ""
#                       OUTPUT_NAME "libxplot")
# 
# get_property(XPLOT_NAME TARGET ${XPLOT_TARGET} PROPERTY OUTPUT_NAME)
# if(MSVC)
#     set(XPLOT_LINK_FILE ${XPLOT_NAME}${CMAKE_LINK_LIBRARY_SUFFIX})
#     set(XPLOT_RUNTIME_FILE ${XPLOT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})
# else()
#     set(XPLOT_LINK_FILE ${XPLOT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})
#     set(XPLOT_RUNTIME_FILE ${XPLOT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})
# endif()

# Tests
# =====

OPTION(BUILD_TESTS "xplot test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(FILES ${XPLOT_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xplot)

install(TARGETS ${XPLOT_TARGET}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xplot)

set(XPLOT_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for xplotConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XPLOT_CMAKECONFIG_INSTALL_DIR})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
              DESTINATION ${XPLOT_CMAKECONFIG_INSTALL_DIR})

############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille and Loic Gouarin       #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.8)
project(xplot)

message(STATUS "Forcing tests build type to Release")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

set(XPLOT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XPLOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configuration
# =============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XPLOT_INSTALL_LIBRARY_DIR "\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"")

configure_file (
    "${XPLOT_INCLUDE_DIR}/xplot/xplot_config_cling.hpp.in"
    "${XPLOT_INCLUDE_DIR}/xplot/xplot_config_cling.hpp"
)

set(MAPFILESPEC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/xplot/map_data)
set(XPLOT_MAPFILESPEC_INSTALL_DIR "share/xplot" CACHE STRING "install path for map files")

install(DIRECTORY ${MAPFILESPEC_DIR}
        DESTINATION ${XPLOT_MAPFILESPEC_INSTALL_DIR})

set(MAPFILE_DIR "\"${CMAKE_INSTALL_PREFIX}/${XPLOT_MAPFILESPEC_INSTALL_DIR}/map_data/\"")

configure_file (
    "${XPLOT_INCLUDE_DIR}/xplot/xmaps_config.hpp.in"
    "${XPLOT_INCLUDE_DIR}/xplot/xmaps_config.hpp"
)

# Versionning
# ===========

file(STRINGS "${XPLOT_INCLUDE_DIR}/xplot/xplot_config.hpp" xplot_version_defines
     REGEX "#define XPLOT_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xplot_version_defines})
    if(ver MATCHES "#define XPLOT_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XPLOT_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XPLOT_VERSION
    ${XPLOT_VERSION_MAJOR}.${XPLOT_VERSION_MINOR}.${XPLOT_VERSION_PATCH})
message(STATUS "xplot version: v${XPLOT_VERSION}")

# Binary version
# See the following URL for explanations about the binary versionning
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html#Updating-version-info
file(STRINGS "${XPLOT_INCLUDE_DIR}/xplot/xplot_config.hpp" xplot_version_defines
    REGEX "#define XPLOT_BINARY_(CURRENT|REVISION|AGE)")
foreach(ver ${xplot_version_defines})
    if(ver MATCHES "#define XPLOT_BINARY_(CURRENT|REVISION|AGE) +([^ ]+)$")
        set(XPLOT_BINARY_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XPLOT_BINARY_VERSION
    ${XPLOT_BINARY_CURRENT}.${XPLOT_BINARY_REVISION}.${XPLOT_BINARY_AGE})
message(STATUS "xplot binary version: v${XPLOT_BINARY_VERSION}")

# Dependencies
# ============

find_package(cppzmq 4.2.3 REQUIRED)
find_package(xtl 0.4 REQUIRED)
find_package(xeus 0.13.0 REQUIRED)
find_package(xwidgets 0.13.0 REQUIRED)

# Source files
# ============

set(XPLOT_HEADERS
    ${XPLOT_INCLUDE_DIR}/xplot/xaxes.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xboxed_container.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xtooltip.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xfigure.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xinteracts.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xmaps_config.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xmarks.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xplot_config.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xplot_config_cling.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xplot.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xscales.hpp
    ${XPLOT_INCLUDE_DIR}/xplot/xtoolbar.hpp
)

set(XPLOT_SOURCES
    ${XPLOT_SOURCE_DIR}/xaxes.cpp
    ${XPLOT_SOURCE_DIR}/xfigure.cpp
    ${XPLOT_SOURCE_DIR}/xmarks.cpp
    ${XPLOT_SOURCE_DIR}/xscales.cpp
    ${XPLOT_SOURCE_DIR}/xtoolbar.cpp
    ${XPLOT_SOURCE_DIR}/xtooltip.cpp
)

# Output
# ======

add_library(xplot SHARED ${XPLOT_SOURCES} ${XPLOT_HEADERS})
target_include_directories(xplot PUBLIC $<BUILD_INTERFACE:${XPLOT_INCLUDE_DIR}>
                                        $<INSTALL_INTERFACE:include>)

target_link_libraries(xplot
    PUBLIC xtl
    PUBLIC xeus
    PUBLIC xwidgets)

set_target_properties(xplot PROPERTIES
                      PUBLIC_HEADER "${XPLOT_HEADERS}"
                      COMPILE_DEFINITIONS "XPLOT_EXPORTS"
                      PREFIX ""
                      VERSION ${XPLOT_BINARY_VERSION}
                      SOVERSION ${XPLOT_BINARY_CURRENT}
                      OUTPUT_NAME "libxplot")

# Compilation flags
# =================

include(CheckCXXCompilerFlag)
string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)
OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

set_target_properties(xplot PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED 14)

target_compile_features(xplot PRIVATE cxx_std_14)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(xplot PUBLIC -Wunused-parameter -Wextra -Wreorder)
    if (DISABLE_ARCH_NATIVE)
        target_compile_options(xplot PUBLIC -mtune=generic)
    else()
        target_compile_options(xplot PUBLIC -march=native)
    endif()

    # Enable link time optimization and set the default symbol
    # visibility to hidden (very important to obtain small binaries)
    if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        # Check for Link Time Optimization support
        # (GCC/Clang)
        CHECK_CXX_COMPILER_FLAG("-flto" HAS_LTO_FLAG)
        if (HAS_LTO_FLAG)
            target_compile_options(xplot PUBLIC -flto)
        endif()

        # Intel equivalent to LTO is called IPO
        if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
            CHECK_CXX_COMPILER_FLAG("-ipo" HAS_IPO_FLAG)
            if (HAS_IPO_FLAG)
                target_compile_options(xplot PUBLIC -ipo)
            endif()
        endif()
    endif()
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

# if(MSVC)
#     target_compile_definitions(xplot PUBLIC -DNOMINMAX)
#     target_compile_options(xplot PUBLIC /DGUID_WINDOWS /MP /bigobj)
#     target_compile_options(xplot PUBLIC /wd4251 /wd 4996)
#     # Allows to compile in debug without requiring each dependencies to
#     # be compiled in debug
#     if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
#         set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
#         message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
#     endif()
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

set(XPLOT_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for xplotConfig.cmake")

install(TARGETS xplot
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xplot)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XPLOT_CMAKECONFIG_INSTALL_DIR})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${XPLOT_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
              DESTINATION ${XPLOT_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
DESTINATION ${XPLOT_CMAKECONFIG_INSTALL_DIR})

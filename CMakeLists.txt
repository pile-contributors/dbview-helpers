# ============================================================================
#
# Introduction
# ------------
#
# This file is the main file for the dbview-helpers. The project follows
# the pattern laid out at http://pile-contributors.github.io/
# for a `pile-helpers` repository.
#
# Usage
# -----
#
# You can use the resources in this project to understand this pile,
# to use it as a model for your own piles or to improve and test this pile.
#
# The project has an optional dependency on Qt5 library. If found,
# the dbview pile will use the definitions for shared libraries.
#
# ============================================================================

set (PROJECT_NAME "dbview-helpers")

project(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8.11)
enable_testing()

option( INCLUDE_PILE_SOURCES_DIRECTLY
        "Use internal dbview as a pile (ON) or as a library (OFF)"
        OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_BINARY_DIR}/build/bin" )
set( EXECUTABLE_OUTPUT_PATH
    "${PROJECT_BINARY_DIR}/build/bin" )
set( LIBRARY_OUTPUT_PATH
    "${PROJECT_BINARY_DIR}/build/lib" )

include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Qt5 COMPONENTS Core Gui Widgets)
if(Qt5Core_FOUND)
    include_directories(
         ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}
         ${Qt5Sql_INCLUDE_DIRS} )
endif()

if(INCLUDE_PILE_SOURCES_DIRECTLY)
    include(pile_support)
    pileInclude (DbView)
    dbviewInit(PILE)
else()
    set (DBVIEW_BUILD_MODE SHARED)
    add_subdirectory(dbview)
endif()

add_subdirectory(tests)

# ============================================================================

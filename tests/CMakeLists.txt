# ============================================================================
#
# This file hosts all tests.
#
# ============================================================================
include_directories("${CMAKE_SOURCE_DIR}/dbview")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/dbview_tests.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/dbview_tests.h")

set(DBVIEW_TEST_HEADERS
    "${CMAKE_CURRENT_BINARY_DIR}/dbview_tests.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sqldb.h"
    )

set(DBVIEW_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/sqldb.cc")

add_subdirectory(unit)
add_subdirectory(integration)

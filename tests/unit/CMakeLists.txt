# ============================================================================
#
# This file hosts all tests.
#
# If INCLUDE_PILE_SOURCES_DIRECTLY is ON then DBVIEW_SOURCES and
# DBVIEW_HEADERS are defined we add them to the executable. DBVIEW_LIBRARY
# is empty.
#
# On the other hand if INCLUDE_PILE_SOURCES_DIRECTLY is
# OFF then DBVIEW_SOURCES and DBVIEW_HEADERS are empty and we link
# against DBVIEW_LIBRARY that is now the name of the target that
# builds the library.
#
# ============================================================================

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if (NOT INCLUDE_PILE_SOURCES_DIRECTLY)
    set (DBVIEW_LIBRARY dbview)
endif()

add_executable(test_basic
    ${DBVIEW_SOURCES}
    ${DBVIEW_HEADERS}
    ${DBVIEW_TEST_HEADERS}
    basic.cc)

if (UNIX)
    find_package(Threads REQUIRED)
    list(APPEND GTEST_BOTH_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    add_definitions(-fPIC)
endif()

target_link_libraries(test_basic
    ${GTEST_BOTH_LIBRARIES}
    ${DBVIEW_LIBRARY})
qt5_use_modules(test_basic Core Gui Widgets Sql)

add_test(
    NAME test_basic
    COMMAND $<TARGET_FILE:test_basic>)

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


if (NOT INCLUDE_PILE_SOURCES_DIRECTLY)
    set (DBVIEW_LIBRARY dbview)
endif()

add_executable(dbview_gui
    ${DBVIEW_SOURCES}
    ${DBVIEW_HEADERS}
    mainwindow.h
    mainwindow.cc
    mainwindow.ui
    main.cc)

if (UNIX)
    find_package(Threads REQUIRED)
    list(APPEND GTEST_BOTH_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    add_definitions(-fPIC)
endif()
qt5_use_modules(dbview_gui Core Gui Widgets Concurrent)

target_link_libraries(dbview_gui
    ${DBVIEW_LIBRARY})

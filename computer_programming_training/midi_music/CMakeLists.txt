cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

set (CMAKE_CXX_STANDARD 17)

if (WIN32)
    aux_source_directory ("src/sheet" LIB_SHEET_SRC)
    add_library (libsheet ${LIB_SHEET_SRC})

    aux_source_directory ("src/visualizer" LIB_VISUALIZER_SRC)
    add_library (libmidivisualizer ${LIB_VISUALIZER_SRC})

    aux_source_directory ("src/sheet_player" LIB_SHEET_PLAYER_SRC)
    add_library (libsheetplayer ${LIB_SHEET_PLAYER_SRC})

    aux_source_directory ("src/keyboard_player" LIB_KEYBOARD_PLAYER_SRC)
    add_library (libkeyboardplayer ${LIB_KEYBOARD_PLAYER_SRC})

    aux_source_directory ("src/util" LIB_UTIL_SRC)
    add_library (libmidiutil ${LIB_UTIL_SRC})

    add_executable (${PROJECT_NAME} "src/main.cpp")
    target_link_libraries (${PROJECT_NAME} libmidiutil libmidivisualizer libkeyboardplayer libsheetplayer libsheet winmm)
endif()

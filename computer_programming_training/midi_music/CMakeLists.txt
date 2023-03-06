cmake_minimum_required (VERSION 3.10)
project (midi_music)
set (CMAKE_CXX_STANDARD 17)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

aux_source_directory (src/sheet LIB_SHEET_SRC)
add_library (libsheet ${LIB_SHEET_SRC})

aux_source_directory (src/visualizer LIB_VISUALIZER_SRC)
add_library (libvisualizer ${LIB_VISUALIZER_SRC})

aux_source_directory (src/sheet_player LIB_SHEET_PLAYER_SRC)
add_library (libsheetplayer ${LIB_SHEET_PLAYER_SRC})

aux_source_directory (src/keyboard_player LIB_KEYBOARD_PLAYER_SRC)
add_library (libkeyboardplayer ${LIB_KEYBOARD_PLAYER_SRC})

aux_source_directory (src/util LIB_UTIL_SRC)
add_library (libutil ${LIB_UTIL_SRC})

add_executable (midi_music "src/main.cpp")
target_link_libraries (midi_music libutil libvisualizer libkeyboardplayer libsheetplayer libsheet winmm)
cmake_minimum_required (VERSION 3.10)
project (sort)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32 AND NOT MSVC)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack=268435456 -static")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK -finput-charset=UTF-8")
endif (WIN32 AND NOT MSVC)

if (WIN32 AND MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8 /execution-charset:gbk /stack:256M")
endif (WIN32 AND MSVC)

aux_source_directory (src/sort LIB_SORT_SRC)
add_library (libsort ${LIB_SORT_SRC})

aux_source_directory (src/rand LIB_RAND_SRC)
add_library (librand ${LIB_RAND_SRC})

aux_source_directory (src/score LIB_SCORE_SRC)
add_library (libscore ${LIB_SCORE_SRC})

add_executable (main src/main.cpp)
target_link_libraries (main libsort librand libscore)
cmake_minimum_required (VERSION 3.10)
project (sort_show)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32 AND NOT MSVC)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK -finput-charset=UTF-8")
endif (WIN32 AND NOT MSVC)

if (WIN32 AND MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8 /execution-charset:gbk")
endif (WIN32 AND MSVC)

aux_source_directory (src/util LIB_UTIL_SRC)
add_library (libutil ${LIB_UTIL_SRC})

aux_source_directory (src/visualizer LIB_VISUALIZER_SRC)
add_library (libvisualizer ${LIB_VISUALIZER_SRC})

aux_source_directory (src/sort LIB_SORT_SRC)
add_library (libsort ${LIB_SORT_SRC})

add_executable (sort_show src/main.cpp)

target_link_libraries (libvisualizer libutil)
target_link_libraries (sort_show libutil libsort libvisualizer winmm)
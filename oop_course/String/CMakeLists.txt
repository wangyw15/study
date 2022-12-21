cmake_minimum_required (VERSION 3.10)
project (week4)

aux_source_directory (src/String LIB_STRING)
add_library (libstring ${LIB_STRING})

add_executable (main src/main.cpp)
target_link_libraries (main libstring)
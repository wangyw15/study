cmake_minimum_required (VERSION 3.10)
project (first_week)

aux_source_directory (src/str LIB_STR)
add_library (libstr ${LIB_STR})

aux_source_directory (src/solve LIB_SOLVE)
add_library (libsolve ${LIB_SOLVE})

aux_source_directory (src/swap LIB_SWAP)
add_library (libswap ${LIB_SWAP})

add_executable (main src/main.cpp)
target_link_libraries (sort libstr libsolve libswap)
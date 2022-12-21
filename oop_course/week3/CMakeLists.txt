cmake_minimum_required (VERSION 3.10)
project (third_week)

aux_source_directory (src/Time LIB_TIME)
add_library (libtime ${LIB_TIME})

aux_source_directory (src/Complex LIB_COMPLEX)
add_library (libcomplex ${LIB_COMPLEX})

add_executable (main src/main.cpp)
target_link_libraries (main libtime libcomplex)
cmake_minimum_required(VERSION 3.10)

project(vector)

aux_source_directory(src/Vector LIB_VECTOR)
add_library(libvector ${LIB_VECTOR})

add_executable(main src/main.cpp)
target_link_libraries(main libvector)
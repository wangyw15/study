cmake_minimum_required(VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${PNAME})

aux_source_directory("src/Vector" LIB_VECTOR)
add_library(libvector ${LIB_VECTOR})

add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} libvector)
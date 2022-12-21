cmake_minimum_required(VERSION 3.10)

project(TemplateLinkList)

aux_source_directory(src/Util UTIL_SRC)
add_library(util ${UTIL_SRC})

add_executable(main "src/main.cpp")
target_link_libraries(main util)
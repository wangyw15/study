cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

file (GLOB SORT_SOURCES "src/sorts/*.cpp")
add_executable ("${PROJECT_NAME}_main" ${SORT_SOURCES} "src/main.cpp")

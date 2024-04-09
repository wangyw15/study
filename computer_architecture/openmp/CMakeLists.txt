cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

find_package (OpenMP REQUIRED)

add_executable ("${PROJECT_NAME}_main" "src/main.c")
target_link_libraries("${PROJECT_NAME}_main" OpenMP::OpenMP_C)

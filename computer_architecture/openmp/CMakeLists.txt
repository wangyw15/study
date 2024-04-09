cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

find_package (OpenMP REQUIRED)

add_executable ("${PROJECT_NAME}_1" "src/requirement1.c")
target_link_libraries("${PROJECT_NAME}_1" OpenMP::OpenMP_C)

add_executable ("${PROJECT_NAME}_2" "src/requirement2.c")
target_link_libraries("${PROJECT_NAME}_2" OpenMP::OpenMP_C)

add_executable ("${PROJECT_NAME}_3" "src/requirement3.c")
target_link_libraries("${PROJECT_NAME}_3" OpenMP::OpenMP_C)

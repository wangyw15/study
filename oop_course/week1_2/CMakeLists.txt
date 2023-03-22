cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

aux_source_directory ("src/str" LIB_STR)
add_library (libstr ${LIB_STR})

aux_source_directory ("src/solve" LIB_SOLVE)
add_library (libsolve ${LIB_SOLVE})

add_executable (${PROJECT_NAME} "src/main.cpp")
target_link_libraries (${PROJECT_NAME} libstr libsolve)
cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

aux_source_directory ("src/String" LIB_STRING)
add_library (libstring ${LIB_STRING})

add_executable (${PROJECT_NAME} src/main.cpp)
target_link_libraries (${PROJECT_NAME} libstring)

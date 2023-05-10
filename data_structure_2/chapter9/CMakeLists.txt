cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

if (WIN32 AND NOT MSVC)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack=268435456 -static")
endif (WIN32 AND NOT MSVC)

if (WIN32 AND MSVC)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /stack:268435456")
endif (WIN32 AND MSVC)

file (GLOB SORT_SOURCES "src/sorts/*.cpp")
add_library ("${PROJECT_NAME}_sort_algorithm" ${SORT_SOURCES})

add_executable ("${PROJECT_NAME}_main" "src/main.cpp")
target_link_libraries("${PROJECT_NAME}_main" "${PROJECT_NAME}_sort_algorithm")

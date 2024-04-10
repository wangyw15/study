cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

find_package (OpenMP REQUIRED)

file (GLOB SOURCES "src/*.c")
foreach (SOURCE ${SOURCES})
    get_filename_component (TARGET ${SOURCE} NAME_WE)
    add_executable ("${PROJECT_NAME}_${TARGET}" ${SOURCE})
    target_link_libraries("${PROJECT_NAME}_${TARGET}" OpenMP::OpenMP_C)
endforeach ()

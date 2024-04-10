cmake_minimum_required (VERSION 3.23 FATAL_ERROR)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME} LANGUAGES CXX CUDA)

set(CMAKE_CUDA_ARCHITECTURES all)

file (GLOB SOURCES "src/*.cu")
foreach (SOURCE ${SOURCES})
    get_filename_component (TARGET ${SOURCE} NAME_WE)
    add_executable ("${PROJECT_NAME}_${TARGET}" ${SOURCE})
endforeach ()

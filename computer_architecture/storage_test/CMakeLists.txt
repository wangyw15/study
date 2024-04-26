cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

file (GLOB SOURCES "src/*.cpp")
foreach (SOURCE ${SOURCES})
    get_filename_component (TARGET ${SOURCE} NAME_WE)
    add_executable ("${PROJECT_NAME}_${TARGET}" ${SOURCE})
    target_compile_features("${PROJECT_NAME}_${TARGET}" PRIVATE cxx_std_17)
endforeach ()

cmake_minimum_required (VERSION 3.10)

# Get project name
get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PNAME})

# Generate target
file (GLOB SOURCES "src/*.cpp")
foreach (SOURCE ${SOURCES})
    get_filename_component (NAME ${SOURCE} NAME_WE)
    add_executable ("${PROJECT_NAME}_${NAME}" ${SOURCE})
endforeach ()

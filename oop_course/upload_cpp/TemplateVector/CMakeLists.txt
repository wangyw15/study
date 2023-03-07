cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project ("upload_${PNAME}")

add_executable (${PROJECT_NAME} "src/main.cpp")

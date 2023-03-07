cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${PNAME})

aux_source_directory ("src/DataStructure" DS_SRC)
add_library (libds ${DS_SRC})
aux_source_directory ("src/Util" EMS_UTIL_SRC)
add_library (libemsutil ${EMS_UTIL_SRC})

add_executable ("${PROJECT_NAME}" "src/main.cpp")
target_link_libraries ("${PROJECT_NAME}" libds libemsutil)
cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${PNAME})

add_subdirectory ("2")
add_subdirectory ("3")
add_subdirectory ("4")
add_subdirectory ("4_sj")
add_subdirectory ("5")
add_subdirectory ("5_sj")
add_subdirectory ("6_sj")
add_subdirectory ("EnterpriseManageSystem")

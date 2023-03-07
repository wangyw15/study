cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${PNAME})

file (GLOB DIRS "chapter*")
foreach (DIR ${DIRS})
    add_subdirectory (${DIR})
endforeach()

add_subdirectory ("seminar1")

if (MSVC)
    add_compile_options ("$<$<C_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
    add_compile_options ("$<$<CXX_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
endif ()

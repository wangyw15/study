cmake_minimum_required (VERSION 3.10)
project (data_structure)

add_subdirectory ("chapter3")
add_subdirectory ("chapter4")
add_subdirectory ("chapter5")
add_subdirectory ("chapter6")
add_subdirectory ("seminar1")

if (MSVC)
    add_compile_options ("$<$<C_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
    add_compile_options ("$<$<CXX_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
endif ()

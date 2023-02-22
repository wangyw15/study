cmake_minimum_required (VERSION 3.10)
project (chapter6)

add_executable(bintree "src/bintree.cpp")
add_executable(falling_balls "src/falling_balls.cpp")

if (MSVC)
    add_compile_options ("$<$<C_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
    add_compile_options ("$<$<CXX_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
endif ()

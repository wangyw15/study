cmake_minimum_required (VERSION 3.10)
project (polynominal)

add_executable (main "src/main.cpp" "src/headers/Functions.h" "src/functions.cpp")

if (MSVC)
    add_compile_options ("$<$<C_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
    add_compile_options ("$<$<CXX_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
endif ()

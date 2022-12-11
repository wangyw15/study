cmake_minimum_required (VERSION 3.10)
project (chapter3)

add_executable (seqlist "src/seqlist.cpp")
add_executable (singlelinklist "src/singlelinklist.cpp")
add_executable (doublelinklist "src/doublelinklist.cpp")

if (MSVC)
    add_compile_options ("$<$<C_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
    add_compile_options ("$<$<CXX_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
endif ()

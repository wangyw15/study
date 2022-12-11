cmake_minimum_required (VERSION 3.10)
project (chapter4)

add_executable (seqstack "src/seqstack.cpp")

if (MSVC)
	add_compile_options ("$<$<C_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
	add_compile_options ("$<$<CXX_COMPILER_ID:MSVC>:/utf-8 /source-charset:utf-8 /execution-charset:gbk>")
endif ()

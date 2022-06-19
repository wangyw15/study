if (WIN32)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK -finput-charset=UTF-8")
endif (WIN32)

aux_source_directory (. LIB_SRC)
add_library (lib ${LIB_SRC})
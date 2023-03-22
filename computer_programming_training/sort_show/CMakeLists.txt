cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (PARENT_PROJECT_NAME)
    set (PNAME "${PARENT_PROJECT_NAME}_${PNAME}")
endif ()
project (${PNAME})

if (WIN32)
    if (NOT MSVC)
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK -finput-charset=UTF-8")
    endif (NOT MSVC)

    if (MSVC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8 /execution-charset:gbk")
    endif (MSVC)

    aux_source_directory ("src/util" LIB_UTIL_SRC)
    add_library (libsortutil ${LIB_UTIL_SRC})

    aux_source_directory ("src/visualizer" LIB_VISUALIZER_SRC)
    add_library (libsortvisualizer ${LIB_VISUALIZER_SRC})

    aux_source_directory ("src/sort" LIB_SORT_SRC)
    add_library (libsort ${LIB_SORT_SRC})

    add_executable (${PROJECT_NAME} "src/main.cpp")

    target_link_libraries (libsortvisualizer libsortutil)
    target_link_libraries (${PROJECT_NAME} libsortutil libsort libsortvisualizer winmm)
endif()

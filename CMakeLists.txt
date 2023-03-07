cmake_minimum_required (VERSION 3.10)

project ("2021CS")

file (GLOB DIRS "*")
foreach (DIR ${DIRS})
    if (IS_DIRECTORY ${DIR})
        get_filename_component (DIR_NAME ${DIR} NAME)
        if (EXISTS "${DIR}/CMakeLists.txt")
            add_subdirectory (${DIR_NAME})
        endif ()
    endif ()
endforeach ()

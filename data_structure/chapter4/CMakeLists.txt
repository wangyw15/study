cmake_minimum_required (VERSION 3.10)

get_filename_component (PNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${PNAME})

# personal work
file (GLOB PERSONAL_SOURCES "personal/*.cpp")
foreach (PERSONAL_SOURCE ${PERSONAL_SOURCES})
    get_filename_component (PERSONAL_SOURCE_NAME ${PERSONAL_SOURCE} NAME_WE)
    add_executable ("${PROJECT_NAME}_personal_${PERSONAL_SOURCE_NAME}" ${PERSONAL_SOURCE})
endforeach ()

# group work
file (GLOB GROUP_SOURCES "group/*.cpp")
foreach (GROUP_SOURCE ${GROUP_SOURCES})
    get_filename_component (GROUP_SOURCE_NAME ${GROUP_SOURCE} NAME_WE)
    add_executable ("${PROJECT_NAME}_group_${GROUP_SOURCE_NAME}" ${GROUP_SOURCE})
endforeach ()

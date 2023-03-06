cmake_minimum_required (VERSION 3.10)
project (chapter3)

# personal work
add_executable ("${PROJECT_NAME}_personal_seqlist" "personal/seqlist.cpp")
add_executable ("${PROJECT_NAME}_personal_singlelinklist" "personal/singlelinklist.cpp")
add_executable ("${PROJECT_NAME}_personal_doublelinklist" "personal/doublelinklist.cpp")

# group work
add_executable ("${PROJECT_NAME}_group_linklistwithouthead" "group/linklist.cpp")
add_executable ("${PROJECT_NAME}_group_function" "group/function.cpp" "group/headers/Functions.cpp")

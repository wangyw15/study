cmake_minimum_required (VERSION 3.10)
project (chapter5)

# personal work
add_executable ("${PROJECT_NAME}_personal_kmp" "personal/kmp.cpp")
add_executable ("${PROJECT_NAME}_personal_matrix" "personal/matrix.cpp")
add_executable ("${PROJECT_NAME}_personal_crosslist" "personal/crosslist.cpp")

# group work
add_executable ("${PROJECT_NAME}_group_linkstring" "group/linkstring.cpp")
add_executable ("${PROJECT_NAME}_group_literatureresearch" "group/literature_research.cpp")

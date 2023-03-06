cmake_minimum_required (VERSION 3.10)
project (chapter6)

# personal work
add_executable ("${PROJECT_NAME}_personal_binary_tree" "personal/binary_tree.cpp")
add_executable ("${PROJECT_NAME}_personal_heap" "personal/heap.cpp")

# group work
add_executable ("${PROJECT_NAME}_group_bintree" "group/bintree.cpp")
add_executable ("${PROJECT_NAME}_group_fallingballs" "group/falling_balls.cpp")

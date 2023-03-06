cmake_minimum_required (VERSION 3.10)
project (chapter4)

# personal work
add_executable ("${PROJECT_NAME}_personal_seqstack" "personal/seqstack.cpp")
add_executable ("${PROJECT_NAME}_personal_seqqueue" "personal/seqqueue.cpp")
add_executable ("${PROJECT_NAME}_personal_linkqueue" "personal/linkqueue.cpp")

# group work
add_executable ("${PROJECT_NAME}_group_BidQueue" "group/BidQueue.cpp")
add_executable ("${PROJECT_NAME}_group_PostfixExpression" "group/PostfixExpression.cpp")
add_executable ("${PROJECT_NAME}_group_TrainDispatching" "group/TrainDispatching.cpp")
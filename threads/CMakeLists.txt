
add_executable(threads_api threads_api.c)

add_executable(producer_consumer producer_consumer.cpp)

add_executable(pipe_ipc pipe_ipc.c)

add_executable(list_structure list_structure.c list_structure_main.cpp)

#find_library(pthread)
#
#target_link_libraries(threads_api
#        pthread)
add_executable(cilent 
    # posix/socket/cilent.cpp
    posix/socket/clinet_pro.cpp
)

add_executable(server
    # posix/socket/serve.cpp
    posix/socket/server2.cpp
)

add_library(yazi_socket STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/posix/socket/src/socket.cpp   # <--- 指向你的 socket.cpp 路径
)

target_include_directories(cilent PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/posix/socket/include)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/posix/socket/include)
target_include_directories(yazi_socket PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/posix/socket/include)

target_link_libraries(server PRIVATE yazi_socket)
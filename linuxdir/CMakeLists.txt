add_executable(cilent 
    # socket/cilent.cpp
    socket/clinet_pro.cpp
)

add_executable(server
    # socket/serve.cpp
    socket/server2.cpp
)

add_library(yazi_socket STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/socket/src/socket.cpp   # <--- 指向你的 socket.cpp 路径
    ${CMAKE_CURRENT_SOURCE_DIR}/socket/src/logger.cpp   # <--- 指向你的 socket.cpp 路径
)

target_include_directories(cilent PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/socket/include
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(server PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/socket/include
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(yazi_socket PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/socket/include)



target_link_libraries(server PRIVATE yazi_socket)


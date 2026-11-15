add_executable(cilent 
    # cilent.cpp
    clinet_pro.cpp
)

add_executable(server
    # serve.cpp
    server2.cpp
)

add_library(yazi_socket STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/socket.cpp   # <--- 指向你的 socket.cpp 路径
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cpp   # <--- 指向你的 socket.cpp 路径
)

target_include_directories(cilent PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(server PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(yazi_socket PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)



target_link_libraries(server PRIVATE yazi_socket)


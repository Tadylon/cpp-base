add_executable(thread_build
    thread-pool/thread_pool.cpp
)

target_include_directories(thread_build PRIVATE ${CMAKE_SOURCE_DIR}/include)

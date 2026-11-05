add_executable(thread_build
    # thread-pool/thread_pool.cpp
    # memory_model/memory_models.cpp
    mutex/thread_mutex.cpp
)

target_include_directories(thread_build PRIVATE ${CMAKE_SOURCE_DIR}/include)

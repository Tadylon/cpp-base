add_executable(container_build
    vector/vector.cpp
)

target_include_directories(container_build PRIVATE ${CMAKE_SOURCE_DIR}/include)


add_executable(template_test
    allocator_t.cpp
    requires/requires.cpp
)
# target_sources(template_test PRIVATE)

target_include_directories(template_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_executable(coroutine_build
    withvalue/value.cpp
)
# target_sources(template_test PRIVATE)

target_include_directories(coroutine_build PRIVATE ${CMAKE_SOURCE_DIR}/include)
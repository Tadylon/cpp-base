add_executable(template_test
    allocator_t.cpp
    requires/requires.cpp
    concept/concept.cpp
    type_traits/type_in_template.cpp
    type_traits/decay_test.cpp
    type_traits/forward_test.cpp
)
# target_sources(template_test PRIVATE)

target_include_directories(template_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
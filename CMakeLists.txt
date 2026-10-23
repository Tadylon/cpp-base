cmake_minimum_required(VERSION 3.30)

# set_target_properties(Main PROPERTIES CXX_MODULE_STD ON)
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "你的CMake版本对应的正确UUID")
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
project(Main CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_MODULE_STD ON)

option(LEARN_BUILD_EXAMPLES      "Build examples"    OFF)
option(LEARN_BUILD_TESTS         "Build tests"       OFF)
option(LEARN_BUILD_TOOLS         "Build tools"       OFF)
option(LEARN_BUILD_MODULE        "Module build"      OFF)
option(LEARN_BUILD_TEMPLATE      "Template build"    ON )
option(LEARN_BUILD_ZLIB          "Zlib build"        OFF)

add_executable(Main
    # STL/Container/map/base_map.cpp
    # STL/Container/map/init_map.cpp
    # function_oop/lambda/auto_lambda.cpp
    # STL/var_type/auto_type.cpp
    # STL/Utility/tuple_pair/tuple_test.cpp
    # STL/Utility/tuple_pair/pair_test.cpp
    # STL/Container/container/define.cpp
    # performance/cache/struct_cache_test.cpp
    # performance/cache/matrix_cache_test.cpp
    # error/stdexcept.cpp
    # coroutine/no_value/simple_generate.cpp
    # coroutine/withvalue/value.cpp
    # coroutine/demo/pro.cpp
    # coroutine/cpp23/generate.cpp
    # coroutine/cpp23/elements_of.cpp
    # coroutine/base/scratch.cpp
    # zlib/zlib.cpp
    key_words/c_extern.cpp
)

target_include_directories(Main PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(LEARN_BUILD_MODULE)
add_subdirectory(module)
endif()

if(LEARN_BUILD_TEMPLATE)
add_subdirectory(template)
endif()

if(LEARN_BUILD_ZLIB)
add_subdirectory(zlib)
endif()
cmake_minimum_required(VERSION 3.30)

# set_target_properties(Main PROPERTIES CXX_MODULE_STD ON)
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

# project(Main CXX)

# set(CMAKE_CXX_MODULE_STD ON)
# set(CMAKE_CXX_SCAN_FOR_MODULES ON)
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(module_test
    # math/test.cpp
    # main.cpp
    import_module.cpp
    # math/math_impl.cpp
    # math/math.ixx
    # math.ixx
)
target_sources(module_test PRIVATE
    FILE_SET CXX_MODULES FILES
        math/math.ixx          # ✅ 仅接口单元
    PRIVATE
        math/math_impl.cpp     # ✅ 实现单元作为普通源文件
)

target_include_directories(module_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
# target_include_directories(module_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/math/include)

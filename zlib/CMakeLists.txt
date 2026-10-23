find_package(ZLIB REQUIRED)

add_executable(zlib-test
    zlib.cpp
)

target_link_libraries(zlib-test PRIVATE ZLIB::ZLIB)
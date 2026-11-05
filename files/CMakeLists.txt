add_executable(files_build
    # FILE_use.cpp
    # stringstream/stringstream_use.cpp
    # Stream/write.cpp
    Stream/read.cpp
)

target_include_directories(files_build PRIVATE ${CMAKE_SOURCE_DIR}/include)

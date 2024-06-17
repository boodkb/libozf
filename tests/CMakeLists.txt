cmake_minimum_required(VERSION 2.8)

project(tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Werror")

set(SOURCE_EXE
    main.cpp
    test_utils.cpp
    details/t_ozf_raw_stream.cpp
    details/t_ozf_encrypted_stream.cpp
    details/utils/t_decode.cpp
    details/utils/t_decompress.cpp
)

include_directories(. ../src)
add_executable(tests ${SOURCE_EXE})
target_link_libraries(tests ozf z)


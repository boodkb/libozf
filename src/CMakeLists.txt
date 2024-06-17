cmake_minimum_required(VERSION 2.8)

project(libozf)

set(TARGET ozf)
set(VERSION "0.1")
set(SOVERSION "0")

set(SOURCE_LIB
    ozf_stream.cpp
    index.cpp
    details/ozf_stream_impl.cpp
    details/utils/decode.cpp
    details/utils/decompress.cpp
)

set(PUBLIC_HEADERS
    ozf_stream.h
    image_parameters.h
    scale.h
    index.h
    tile_index.h
    exceptions/exception.h
    exceptions/unsupported_exception.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++1y -Wall -Werror")

include_directories(.)
add_library(${TARGET} SHARED ${SOURCE_LIB})
set_target_properties(${TARGET} PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})


set(INSTALL_LIB_DIR "lib")
set(INSTALL_INC_DIR "include/ozf")
set(INSTALL_PKGCONFIG_DIR "share/pkgconfig")

configure_file( ${CMAKE_SOURCE_DIR}/libozf.pc.in
                ${CMAKE_BINARY_DIR}/libozf.pc @ONLY)

include(cmake/install_headers.cmake)

install(FILES ${CMAKE_BINARY_DIR}/libozf.pc DESTINATION ${INSTALL_PKGCONFIG_DIR})
install(TARGETS ${TARGET} LIBRARY DESTINATION ${INSTALL_LIB_DIR})
install_headers_with_directory(${INSTALL_INC_DIR} PUBLIC_HEADERS)


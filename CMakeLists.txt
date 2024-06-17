cmake_minimum_required(VERSION 3.5)

project(libozf)

add_subdirectory(src)

enable_testing()

if(BUILD_TESTING)
  add_subdirectory(tests)
  set(TEST_DIRECTORY ${CMAKE_SOURCE_DIR})
  add_test(tests tests/tests working_directory ${TEST_DIRECTORY})
endif()

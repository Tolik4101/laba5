cmake_minimum_required(VERSION 3.4)
set(COVERAGE OFF CACHE BOOL "Coverage")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
project (sborkafinal)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gtest" "gtest")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/banking")
add_executable(banki test/banktest.cpp)
if(COVERAGE)
	target_compile_options(banki PRIVATE --coverage)
	target_link_libraries(banki PRIVATE --coverage)
endif()
target_include_directories(banki PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/banking")
target_link_libraries(banki PRIVATE bank gtest gtest_main gmock_main)


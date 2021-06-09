cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(boost/googletest)

include_directories(boost/googletest/googletest/include)
add_executable(lab3 main.cpp tree.h heap.h queue.h test.cpp)
target_link_libraries(lab3 gtest)
cmake_minimum_required(VERSION 3.20)
project(IraDanceva_YMP_1)
set(CMAKE_CXX_STANDARD 20)

include(conan_libraries/conan_paths.cmake)
find_package(GTest)

add_library(${PROJECT_NAME}_objs
        src/containers/forward_list.hpp
        src/containers/forward_list.cpp
        src/tasks/first.hpp
        src/tasks/first.cpp)

#Unit Tests
include(GoogleTest)
add_executable( ${PROJECT_NAME}_tests
        tests/basic.cpp
        tests/first_task.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        GTest::gtest
        GTest::gtest_main
        ${PROJECT_NAME}_objs)

#Main
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)
cmake_minimum_required(VERSION 3.0.0)

project(aplysia VERSION 0.0.1)

add_library(${PROJECT_NAME} source/fnn.cpp source/nsnn.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(main_test main.cpp)
target_link_libraries(main_test ${PROJECT_NAME})

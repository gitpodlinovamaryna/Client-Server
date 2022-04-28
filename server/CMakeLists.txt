cmake_minimum_required(VERSION 3.0.0)

project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SRC_LIST main.cpp sources/functions_for_server.cpp sources/server.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
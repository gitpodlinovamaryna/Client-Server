cmake_minimum_required(VERSION 3.8.1)
project(server)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_library(${PROJECT_NAME}
            server.cpp
            functions_for_server.cpp
            main.cpp
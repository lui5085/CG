cmake_minimum_required(VERSION 3.29)
project(CG)

set(CMAKE_CXX_STANDARD 20)

add_executable(CG main.cpp
        funcoes.cpp)

target_link_libraries(CG -lglut -lglfw -lGLEW -lGL -lGLU)

cmake_minimum_required(VERSION 3.29)
project(CG)

set(CMAKE_CXX_STANDARD 20)

add_executable(CG
        lib/funcoes.cpp
        lib/funcoes.h
        lib/Plane.cpp
        lib/Plane.h
        lib/Sphere.cpp
        lib/Sphere.h
        lib/Ray.cpp
        lib/Ray.h
        td3.cpp
        )

target_link_libraries(CG -lglut -lglfw -lGLEW -lGL -lGLU)
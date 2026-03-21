cmake_minimum_required(VERSION 3.29)
project(projekt_algorytmy)

set(CMAKE_CXX_STANDARD 17)

add_executable(projekt_algorytmy
        src/main.cpp
)

target_include_directories(projekt_algorytmy PRIVATE include)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
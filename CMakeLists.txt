cmake_minimum_required(VERSION 3.29)
project(projekt_algorytmy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(projekt_algorytmy
        src/main.cpp
        include/DoublyLinkedList.h
        include/SinglyLinkedList.h
        include/Array.h
        src/FileReader.cpp
        include/FileReader.h
        include/Types.h
)

target_include_directories(projekt_algorytmy PRIVATE include)

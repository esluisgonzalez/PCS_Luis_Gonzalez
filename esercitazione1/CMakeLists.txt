cmake_minimum_required(VERSION 3.20)

project(esercitazione_01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

add_executable(programma programma.cpp)
add_executable(calcolo_temperatura_media calcolo_temperatura_media.cpp)
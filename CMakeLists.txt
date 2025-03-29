cmake_minimum_required(VERSION 3.30)
project(DA_ShortestPath)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA_ShortestPath src/Graph.h
        src/readData.h
        src/menu.cpp
        src/Node.h
        src/Edge.h
        src/Graph.cpp
        src/main.cpp
        src/driving-walking.cpp
        src/bash.cpp
)

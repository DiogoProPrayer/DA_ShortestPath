cmake_minimum_required(VERSION 3.30)
project(DA_ShortestPath)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA_ShortestPath src/Graph.h
        src/readData.h
        src/Menu.cpp
        src/Node.h
        src/Edge.h
        src/Drive.h
)

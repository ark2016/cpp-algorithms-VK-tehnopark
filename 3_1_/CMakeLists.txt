cmake_minimum_required(VERSION 3.28)
project(task_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_1 main.cpp
        IGraph.h
        ListGraph.h
        ListGraph.cpp
        MatrixGraph.h
        MatrixGraph.cpp
        SetGraph.h
        SetGraph.cpp
        ArcGraph.cpp
        ArcGraph.h)

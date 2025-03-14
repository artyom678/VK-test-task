cmake_minimum_required(VERSION 3.28.3)

project(ShortestDistance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shortest_distance shortest_distance.cpp)

configure_file(graph.txt ${CMAKE_BINARY_DIR}/graph.txt COPYONLY)
cmake_minimum_required(VERSION 3.17)
project(CookingMamas)

set(CMAKE_CXX_STANDARD 14)

add_executable(CookingMamas main.cpp AdjacencyList.cpp AdjacencyList.h Recipe.cpp Recipe.h PriorityQueue.cpp PriorityQueue.h)
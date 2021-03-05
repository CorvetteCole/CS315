cmake_minimum_required(VERSION 3.17)
project(project_1_trains)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_1_trains trains.cpp DoublyLinkedList.h Train.cpp Train.h)
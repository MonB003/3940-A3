cmake_minimum_required(VERSION 3.23)
project(A3)

set(CMAKE_CXX_STANDARD 14)

add_executable(A3 main.cpp ServerSocket.cpp ServerSocket.hpp ServerThread.cpp ServerThread.hpp)

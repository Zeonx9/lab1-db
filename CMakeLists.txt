cmake_minimum_required(VERSION 3.23)
project(DataBaseLabse)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataBaseLabse main.cpp db.cpp db.h scheme.cpp scheme.h)

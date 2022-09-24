cmake_minimum_required(VERSION 3.23)
project(DataBaseLabse)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataBaseLabse a_main.cpp table.cpp table.h scheme.cpp scheme.h db.cpp db.h)

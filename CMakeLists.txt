cmake_minimum_required(VERSION 3.22)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(compiler main.cpp
        headers/util.hpp
        headers/token.hpp
        headers/lexer.hpp
        headers/util.hpp
        source/lexer.cpp
        source/token.cpp
        source/util.cpp)

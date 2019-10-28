cmake_minimum_required(VERSION 3.10)
project(FEUP-AEDA-Proj1)

set(CMAKE_CXX_STANDARD 11)

file(GLOB FEUP-AEDA-Proj1_SRC
        "include/*.h"
        "src/*.cpp"
        "main.cpp"
        )

add_executable(FEUP-AEDA-Proj1 ${FEUP-AEDA-Proj1_SRC})


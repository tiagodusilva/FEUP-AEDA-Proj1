cmake_minimum_required(VERSION 3.10)
project(FEUP-AEDA-Proj1)

set(CMAKE_CXX_STANDARD 11)

add_executable(FEUP-AEDA-Proj1 main.cpp src/address.cpp src/cards.cpp src/date.cpp src/enterprise.cpp src/event.cpp src/museum.cpp src/time.cpp src/utilities.cpp include/address.h include/cards.h include/date.h include/enterprise.h include/event.h include/museum.h include/time.h include/utilities.h)

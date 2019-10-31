cmake_minimum_required(VERSION 3.10)
project(FEUP-AEDA-Proj1)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)

file(GLOB FEUP-AEDA-Proj1_FILES
        "include/*.h"
        "src/*.cpp"
        "tests/*.cpp"
        "lib/googletest-master/googlemock/include/*"
        "lib/googletest-master/googletest/include/*"
        )

add_executable(FEUP-AEDA-Proj1 ${FEUP-AEDA-Proj1_FILES} main.cpp)
target_link_libraries(FEUP-AEDA-Proj1 gtest gtest_main)

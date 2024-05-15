cmake_minimum_required(VERSION 3.13)
project(Neural_Network 
VERSION 1.0
DESCRIPTION "Neurol Network for predicting digits"
LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    add_compile_options(
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
endif()

add_executable(network
main.cpp
Functions.cpp
Layer.cpp
LinAlg.cpp
MnistReader.cpp
Network.cpp)

add_executable(convert ConvertMnistDataToTxt.cpp)
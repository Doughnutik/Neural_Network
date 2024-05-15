cmake_minimum_required(VERSION 3.13)
project(Neural_Network 
VERSION 1.0
DESCRIPTION "Neurol Network for predicting digits"
LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

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
Network.cpp
Functions.cpp
Layer.cpp
LinAlg.cpp
MnistReader.cpp
main.cpp)

add_executable(convert ConvertMnistDataToTxt.cpp)
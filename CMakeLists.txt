cmake_minimum_required(VERSION 3.14)

project(Enigma)

file(GLOB SRC src/*.cpp)

add_executable(Enigma ${SRC})
target_include_directories(Enigma PUBLIC src/)

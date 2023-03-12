cmake_minimum_required(VERSION 3.14)

project(Enigma)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
file(GLOB SRC src/*.cpp src/Objects/*.cpp)

option(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Enigma ${SRC})
target_include_directories(Enigma PUBLIC src/ glfw GLAD)
target_link_libraries(Enigma PUBLIC glfw GLAD glm)

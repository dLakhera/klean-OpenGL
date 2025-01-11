cmake_minimum_required(VERSION 3.0.0)

project(klean VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "-Wall")

message("CXX Standard: ${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES 
    src/config.h 
    src/main.cpp
    src/glad.c
    src/triangle_mesh.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

message(${CMAKE_BINARY_DIR})
message(${CMAKE_HOME_DIRECTORY})
message(${CMAKE_SOURCE_DIR})
# message(${CMAKE_INCLUDE_DIR})


add_executable(klean ${SOURCES})
target_include_directories(klean PRIVATE dependencies)

target_link_libraries(klean glfw OpenGL::GL)


cmake_minimum_required(VERSION 3.5)
project(break_the_bricks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        README.md src/game.cpp src/game.h src/objects.cpp src/objects.h src/util.cpp src/util.h src/main.cpp src/constants.h)

add_executable(break_the_bricks ${SOURCE_FILES})

target_link_libraries(break_the_bricks GL GLU glut)

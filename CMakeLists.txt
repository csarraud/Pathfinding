cmake_minimum_required(VERSION 3.11)
project(pathfinding)

#look for SFML and add it
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})
find_package (SFML REQUIRED COMPONENTS system window graphics network audio)

include_directories(
    include
    ${SFML_INCLUDE_DIR})

set(SRC src/pathfinding.cpp)

add_executable(pathfinding ${SRC})
target_link_libraries(pathfinding sfml-graphics sfml-audio)
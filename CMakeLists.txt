cmake_minimum_required(VERSION 3.20)
project(battleship)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_IMAGE REQUIRED)
find_package(jsoncpp REQUIRED)

add_executable(battleship
    src/main.cpp
    src/battleship_game.cpp
    src/grid.cpp
    src/cell.cpp
    src/engine/configuration.cpp
    src/engine/engine.cpp
    src/engine/entity.cpp
    src/engine/game.cpp
    src/engine/image.cpp
    src/engine/path_factory.cpp
    src/engine/position.cpp
    src/engine/resolution.cpp
    src/engine/resource_manager.cpp
)

target_include_directories(
    battleship 
    PUBLIC 
    include 
    ${SDL3_INCLUDE_DIRS}
)

target_link_libraries(
    battleship 
    PRIVATE 
    SDL3::SDL3 
    SDL3_image::SDL3_image 
    jsoncpp_lib
)
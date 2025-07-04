cmake_minimum_required(VERSION 3.20)
project(battleship)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3
find_package(SDL3 REQUIRED)

# Find SDL3_Image
find_package(SDL3_IMAGE QUIET)

if (NOT SDL3_IMAGE_FOUND)
    find_package(SDL3_image QUIET)
    if (SDL3_image_FOUND)
        set(SDL3_IMAGE_FOUND TRUE)
        set(SDL3_IMAGE_INCLUDE_DIRS ${SDL3_image_INCLUDE_DIRS})
        set(SDL3_IMAGE_LIBRARIES ${SDL3_image_LIBRARIES})
    endif()
endif()

if (NOT SDL3_IMAGE_FOUND)
    message(FATAL_ERROR "SDL3_image not found! Make sure it is installed.")
endif()

# Find jsoncpp
find_package(jsoncpp QUIET)

if (jsoncpp_FOUND)
    set(JSONCPP_INCLUDE_DIRS ${jsoncpp_INCLUDE_DIRS})
    set(JSONCPP_LIBRARIES jsoncpp_lib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP REQUIRED jsoncpp)
endif()

add_executable(battleship
    src/main.cpp
    src/battleship_game.cpp
    src/grid.cpp
    src/cell.cpp
    src/ship.cpp
    src/battleship.cpp
    src/carrier.cpp
    src/cruiser.cpp
    src/submarine.cpp
    src/destroyer.cpp
    src/start_button.cpp
    src/engine/configuration.cpp
    src/engine/dimensions.cpp
    src/engine/engine.cpp
    src/engine/entity.cpp
    src/engine/game.cpp
    src/engine/image.cpp
    src/engine/path_factory.cpp
    src/engine/position.cpp
    src/engine/resolution.cpp
    src/engine/resource_manager.cpp
    src/engine/sprite.cpp
)

target_include_directories(
    battleship 
    PUBLIC 
    include 
    ${SDL3_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIRS}
)

target_link_libraries(
    battleship 
    PRIVATE 
    SDL3::SDL3 
    SDL3_image::SDL3_image 
    ${JSONCPP_LIBRARIES}
)
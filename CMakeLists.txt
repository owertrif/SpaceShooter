cmake_minimum_required(VERSION 3.6)
project(ClionTest)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp src/Game.cpp headers/Game.h src/Player.cpp headers/Player.h src/Bomb.cpp headers/Bomb.h src/Meteor.cpp headers/Meteor.h src/Button.cpp headers/Button.h src/Pagination.cpp headers/Pagination.h)
add_executable(ClionTest ${SOURCE_FILES})

include_directories(headers src textures)

set(SFML_DIR "E:/libs/clion_libs/SFML/lib/cmake/SFML")

target_link_libraries(ClionTest sfml-graphics-d sfml-system-d sfml-window-d)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)



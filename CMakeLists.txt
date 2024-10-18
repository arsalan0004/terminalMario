cmake_minimum_required(VERSION 3.28.3)

project(TerminalMario)

add_library(game    STATIC cpp/game.cpp)
add_library(mario    STATIC cpp/marioFx.cpp)

add_executable(${PROJECT_NAME} cpp/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC game)
target_link_libraries(game PUBLIC mario)



cmake_minimum_required(VERSION 3.0.0)

set(PROJECTNAME PongGame)
project(${PROJECTNAME} VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/export/bin)

add_compile_options(
-Wall
-Wextra
-Wshadow 
-Wnon-virtual-dtor
-Wpedantic
-pedantic
)

set(SOURCEFILES
src/main.cpp
src/pong.cpp
src/state_manager.cpp
)

set(HEADERFILES
src/state_interface.hpp
src/pong.hpp
src/state_manager.hpp
)

add_executable(${PROJECTNAME} ${SOURCEFILES})
target_include_directories(${PROJECTNAME} PRIVATE include/)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECTNAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECTNAME} PRIVATE imgui::imgui)

find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(${PROJECTNAME} PRIVATE ImGui-SFML::ImGui-SFML)
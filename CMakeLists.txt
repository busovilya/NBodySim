project(nbodysim)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(HEADERS src/body.h src/button.h src/force.h src/simulation.h src/simulation_window.h src/text_panel.h src/math.h src/graphic_primitives.h src/config_parser.h)
set(SOURCES src/body.cpp src/button.cpp src/force.cpp src/simulation.cpp src/simulation_window.cpp src/text_panel.cpp src/math.cpp src/graphic_primitives.cpp src/config_parser.cpp)

add_library(yaml libs/mini-yaml/yaml/Yaml.cpp libs/mini-yaml/yaml/Yaml.hpp)
add_executable(${PROJECT_NAME} src/main.cpp ${HEADERS} ${SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(SFML 2 REQUIRED system window graphics network audio)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${SFML_INCLUDE_DIR})
include_directories(libs/mini-yaml)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
target_link_libraries(${PROJECT_NAME} yaml)
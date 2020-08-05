project(nbodysim)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(HEADERS src/body.h src/button.h src/force.h src/simulation.h src/simulation_window.h src/text_panel.h src/math.h src/graphic_primitives.cpp)
set(SOURCES src/body.cpp src/button.cpp src/force.cpp src/simulation.cpp src/simulation_window.cpp src/text_panel.cpp src/math.cpp src/graphic_primitives.h)

add_executable(${PROJECT_NAME} src/main.cpp ${HEADERS} ${SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(SFML 2 REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
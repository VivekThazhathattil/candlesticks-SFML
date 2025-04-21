cmake_minimum_required(VERSION 3.25)

project(test_sfml VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    test_plotter.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    candlestick_sfml
    sfml-graphics
    sfml-window
    sfml-system
)


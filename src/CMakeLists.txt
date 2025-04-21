cmake_minimum_required(VERSION 3.25)

project(candlestick_sfml VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME}
    SRLevels.cpp
    candlestick.cpp
    dataHandler.cpp
    plotter.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)


cmake_minimum_required(VERSION 3.16)
project(HexBinCharEditor LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(HexBinCharEditor
    main.cpp
    hexbinchareditor.h
    hexbinchareditor.cpp
)

target_link_libraries(HexBinCharEditor PRIVATE Qt6::Widgets)

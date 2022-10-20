cmake_minimum_required(VERSION 3.5)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (PROJECT_NAME typer)
set (SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set (RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")


project("${PROJECT_NAME}" LANGUAGES CXX)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file (GLOB_RECURSE SOURCES
            "${SOURCE_DIR}/*.h"
            "${SOURCE_DIR}/*.hpp"
            "${SOURCE_DIR}/*.cpp"
            "${SOURCE_DIR}/gui/*.h"
            "${SOURCE_DIR}/gui/*.hpp"
            "${SOURCE_DIR}/gui/*.cpp"
            "${RESOURCE_DIR}/*.qrc")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network)

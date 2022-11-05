cmake_minimum_required(VERSION 3.5)

set (PROJECT_NAME typer)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set (RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network NetworkAuth )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network NetworkAuth )

#todo separate cmakelist
set(PROJECT_SOURCES
        "${SOURCE_DIR}/main.cpp"
        "${SOURCE_DIR}/gui/EnterMenu.cpp"
        "${SOURCE_DIR}/gui/EnterMenu.h"
        "${SOURCE_DIR}/gui/MainWindow.cpp"
        "${SOURCE_DIR}/gui/MainWindow.h"
        "${SOURCE_DIR}/gui/SettingsWidget.cpp"
        "${SOURCE_DIR}/gui/SettingsWidget.h"
        "${SOURCE_DIR}/gui/TextEditRenderer.cpp"
        "${SOURCE_DIR}/gui/TextEditRenderer.h"
        "${SOURCE_DIR}/gui/TyperWidget.cpp"
        "${SOURCE_DIR}/gui/TyperWidget.h"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                              Qt${QT_VERSION_MAJOR}::Network
                                              Qt${QT_VERSION_MAJOR}::NetworkAuth)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

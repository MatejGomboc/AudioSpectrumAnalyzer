cmake_minimum_required(VERSION 3.16.0)

project(audio_spectrum_analyzer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 COMPONENTS REQUIRED Core Gui Widgets)

add_executable(audio_spectrum_analyzer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    waterfallplot.cpp
    waterfallplot.h
    resources.qrc
)

target_link_libraries(audio_spectrum_analyzer PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(audio_spectrum_analyzer PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

target_compile_definitions(audio_spectrum_analyzer PRIVATE
    QT_DEPRECATED_WARNINGS
)

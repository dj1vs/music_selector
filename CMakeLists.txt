cmake_minimum_required(VERSION 3.16)

project(music_selector VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        disk.h disk.cpp
        album.h album.cpp
        parseconfig.h
        diskwidget.h diskwidget.cpp diskwidget.ui
        mainwindow.ui
        pch.h
)

qt_add_executable(music_selector
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    newdiskdialog.h newdiskdialog.cpp newdiskdialog.ui


)

target_link_libraries(music_selector PRIVATE Qt6::Widgets Qt6::Core)

target_precompile_headers(music_selector PRIVATE pch.h)


qt_finalize_executable(music_selector)


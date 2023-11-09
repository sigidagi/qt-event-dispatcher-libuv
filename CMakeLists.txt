cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(libuv-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Don't use e.g. GNU extension (like -std=gnu++11) for portability
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CPM)
# Add targets for formating cpp and cmake files. See README.md
CPMAddPackage("gh:libuv/libuv@1.46.0")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")
CPMAddPackage("gh:skypjack/uvw@3.2.0_libuv_v1.46")

add_compile_options(
    -g
    -Wall
    -Wextra
    -Wno-unused-parameter
)

find_package(QT NAMES Qt5)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED
    Core
    Gui
    Widgets
    Xml
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

message(STATUS "libuv source dir: ${uvw_SOURCE_DIR}")

add_subdirectory(src/networking)
add_subdirectory(src/dispatcher)
add_subdirectory(src/app)


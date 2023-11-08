cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(qt-event-dispatcher-libuv)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Don't use e.g. GNU extension (like -std=gnu++11) for portability
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CPM)
# Add targets for formating cpp and cmake files. See README.md
CPMAddPackage("gh:libuv/libuv@1.47.0")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

set(PUBLIC
    src/eventdispatcherlibuv.h
)

set(SOURCES
    src/eventdispatcherlibuv_p.h
    src/eventdispatcherlibuv.cpp
    src/eventdispatcherlibuv/async_channel.cpp
    src/eventdispatcherlibuv/timer_notifier.cpp
    src/eventdispatcherlibuv/time_tracker.cpp
    src/eventdispatcherlibuv/libuv_api.cpp
    src/eventdispatcherlibuv/socket_notifier.cpp
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

add_library(${PROJECT_NAME} STATIC ${PUBLIC} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
    PUBLIC ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    uv
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)
#set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

add_subdirectory(test)


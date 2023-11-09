cmake_minimum_required(VERSION 3.16)

project(qt-event-dispatcher-libuv)

set(PUBLIC
    eventdispatcherlibuv.h
)

set(SOURCES
    eventdispatcherlibuv_p.h
    eventdispatcherlibuv.cpp
    eventdispatcherlibuv/async_channel.cpp
    eventdispatcherlibuv/timer_notifier.cpp
    eventdispatcherlibuv/time_tracker.cpp
    eventdispatcherlibuv/libuv_api.cpp
    eventdispatcherlibuv/socket_notifier.cpp
)

add_library(${PROJECT_NAME} STATIC ${PUBLIC} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    uv
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)


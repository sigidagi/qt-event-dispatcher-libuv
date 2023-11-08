cmake_minimum_required(VERSION 3.16)

project(SimpleEvent)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    images.qrc
    teamview.cpp
    teammemberview.cpp
    teammembermodel.cpp
    addmemberdialog.cpp
    xmlhandler.cpp
    #websocket/websocket.cpp
    #websocket/url.cpp
)

message(STATUS "QT include: ${Qt5_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    qt-event-dispatcher-libuv
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/cppcodec
)

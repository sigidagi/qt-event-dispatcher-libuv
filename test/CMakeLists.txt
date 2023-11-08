cmake_minimum_required(VERSION 3.16)

project(SimpleEvent)

message(STATUS "QT include: ${Qt5_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    qt-event-dispatcher-libuv
)


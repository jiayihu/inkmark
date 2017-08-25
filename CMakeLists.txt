cmake_minimum_required(VERSION 3.6)
project(inkmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_AUTOMOC ON)
set(SOURCE_FILES main.cpp)
find_package(Qt5Widgets REQUIRED)
add_executable(inkmark ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)

target_link_libraries(inkmark src)

find_package(Qt5Svg REQUIRED)
target_link_libraries(inkmark Qt5::Widgets)

file(COPY src/assets/ DESTINATION ./)

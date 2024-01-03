cmake_minimum_required(VERSION 3.18)

project(day10)

set(CLIENT_SOURCE client.cpp)
set(SERVER_SOURCE server.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall ")
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)


find_package(Threads REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 创建一个静态库
add_library(${PROJECT_NAME}-Lib STATIC ${ALL_SOURCES})

add_executable(${PROJECT_NAME}-Client ${CLIENT_SOURCE})
add_executable(${PROJECT_NAME}-Server ${SERVER_SOURCE})
add_executable(${PROJECT_NAME}-ThreadPoolTest ThreadPoolTest.cpp)

target_link_libraries(${PROJECT_NAME}-Client ${PROJECT_NAME}-Lib)
target_link_libraries(${PROJECT_NAME}-Server ${PROJECT_NAME}-Lib)
target_link_libraries(${PROJECT_NAME}-ThreadPoolTest ${PROJECT_NAME}-Lib)

target_link_libraries(${PROJECT_NAME}-Lib Threads::Threads)
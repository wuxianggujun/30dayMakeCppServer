cmake_minimum_required(VERSION 3.18)

project(day03)

set(CLIENT_SOURCE ${CMAKE_CURRENT_LIST_DIR}/client.cpp)
set(SERVER_SOURCE ${CMAKE_CURRENT_LIST_DIR}/server.cpp)

message(STATUS "CLIENT_SOURCE: ${CLIENT_SOURCE}")

file(GLOB_RECURSE ALL_SOURCES *.cpp *.hpp)

list(REMOVE_ITEM ALL_SOURCES ${CLIENT_SOURCE} ${SERVER_SOURCE})
message(STATUS "ALL_SOURCES: ${ALL_SOURCES}")

add_executable(${PROJECT_NAME}-Client ${CLIENT_SOURCE} ${ALL_SOURCES})
add_executable(${PROJECT_NAME}-Server ${SERVER_SOURCE} ${ALL_SOURCES})

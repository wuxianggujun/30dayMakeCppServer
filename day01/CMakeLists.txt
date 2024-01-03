cmake_minimum_required(VERSION 3.18)

project(day01)

set(CLIENT_SOURCE client.cpp)
set(SERVER_SOURCE server.cpp)

add_executable(${PROJECT_NAME}-Client ${CLIENT_SOURCE})
add_executable(${PROJECT_NAME}-Server ${SERVER_SOURCE})

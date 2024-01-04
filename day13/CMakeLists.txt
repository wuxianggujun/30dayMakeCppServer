cmake_minimum_required(VERSION 3.18)

project(day13 VERSION 0.1 DESCRIPTION "Day13" LANGUAGES C CXX)

#set(CLIENT_SOURCE test/client.cpp)
#set(SERVER_SOURCE test/server.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall ")
set(CMAKE_BUILD_TYPE Debug)

# Output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


file(GLOB_RECURSE ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
add_library(day_shared SHARED ${ALL_SOURCES})

find_package(Threads REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)

target_link_libraries(day_shared Threads::Threads)
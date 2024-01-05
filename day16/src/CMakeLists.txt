file(GLOB_RECURSE ALL_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(day_shared SHARED ${ALL_SOURCES})

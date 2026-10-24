cmake_minimum_required(VERSION 3.25)
project(dynarsaur C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

## Set the output directory for all built objects
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

## Add all c source files & Headers
file(GLOB SOURCES "src/*.c")
add_library(dynarsaur ${SOURCES})

# Headers
target_include_directories(dynarsaur PUBLIC ${PROJECT_SOURCE_DIR}/include)

## Test Program
option(BUILD_TEST "Build the test program" ON)

if (BUILD_TEST)
    add_executable(Tests main.c)
    target_link_libraries(Tests PRIVATE dynarsaur)
endif()

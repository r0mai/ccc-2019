cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

find_package(Boost)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(solve
    src/main.cpp
)

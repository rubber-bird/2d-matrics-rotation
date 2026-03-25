cmake_minimum_required(VERSION 3.12)

project(2DRotation CXX)

add_executable(2DRotation
    src/main.cpp
    src/matrix.cpp
    src/forward-projection.cpp
    src/back-projection.cpp
)

set_property(TARGET 2DRotation PROPERTY CXX_STANDARD 17)
set_property(TARGET 2DRotation PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(2DRotation PRIVATE src)

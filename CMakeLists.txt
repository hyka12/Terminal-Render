cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

add_executable(MyProgram)

target_sources(MyProgram PRIVATE
    src/main.cpp
    src/frame.cpp
    src/framebuffer.cpp
)

target_include_directories(MyProgram PRIVATE $(CMAKE_CURRENT_SOURCE_DIR)/include)

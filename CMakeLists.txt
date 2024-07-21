cmake_minimum_required(VERSION 3.0)
project(cpplox)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")
add_executable(cpplox ${SOURCES})
set_property(TARGET cpplox PROPERTY CXX_STANDARD 20)

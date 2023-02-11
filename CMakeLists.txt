cmake_minimum_required(VERSION 3.12)

project(ray_tracer)

add_subdirectory(googletest)

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(raytracertests tests.cpp) # add this executable

target_link_libraries(raytracertests PRIVATE gtest) # link google test to this executable
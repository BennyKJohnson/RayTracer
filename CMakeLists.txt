cmake_minimum_required(VERSION 3.12)

project(ray_tracer)

add_subdirectory(googletest)

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

set(SOURCES FloatHelper.cpp Tuple.cpp tests.cpp)
set(HEADERS FloatHelper.h Tuple.h)

add_executable(raytracertests ${SOURCES} ${HEADERS}) # add this executable
target_include_directories(raytracertests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(raytracertests PRIVATE gtest) # link google test to this executable
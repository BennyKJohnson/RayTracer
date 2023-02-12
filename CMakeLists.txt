cmake_minimum_required(VERSION 3.12)

project(ray_tracer)

add_subdirectory(googletest)

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

set(SOURCES source/FloatHelper.cpp source/Tuple.cpp tests.cpp)
set(HEADERS source/FloatHelper.h source/Tuple.h)

add_executable(raytracertests ${SOURCES} ${HEADERS}) # add this executable
target_include_directories(raytracertests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_link_libraries(raytracertests PRIVATE gtest) # link google test to this executable
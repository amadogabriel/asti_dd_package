cmake_minimum_required (VERSION 3.2)
project( dd_package LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -DNDEBUG -g0 -O3")

# add -fopenmp flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(dd_example ${SOURCES})
include_directories(src)

# Include OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    target_link_libraries(dd_example PUBLIC OpenMP::OpenMP_CXX)
endif()


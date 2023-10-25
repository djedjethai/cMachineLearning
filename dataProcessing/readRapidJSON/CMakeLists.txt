cmake_minimum_required(VERSION 3.0)
project(readJSON)


set(Boost_LIBRARY_DIRS "/usr/lib" CACHE PATH "Path to boost")
set(EIGEN_PATH "/home/jerome/clibs/headers/Eigen" CACHE PATH "Path to eigen")

if(NOT EIGEN_PATH)
  message(FATAL_ERROR "Missing Eigen install path, please specify EIGEN_PATH")
else()
  message("Eigen path is ${EIGEN_PATH}")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED COMPONENTS serialization)

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Define your project's source files
set(SOURCES
    main.cc
    reviewsreader.cpp
    paper.h
    review.h
    reviewsreader.h
)

# link_directories(${Boost_LIBRARY_DIRS} ${EIGEN_PATH}) // should not be use anymore
include_directories(${Boost_LIBRARY_DIRS} ${EIGEN_PATH})  # Add Eigen & Boost include directory

add_executable(read-json ${SOURCES})
target_link_libraries(read-json cblas ${Boost_LIBRARIES} stdc++fs)


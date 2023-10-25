cmake_minimum_required(VERSION 3.0)
project(readCSVWithDlib)


set(DLIB_PATH "/home/jerome/clibs/dlibBUILT/lib" CACHE PATH "Path to dlib")
set(Boost_LIBRARY_DIRS "/usr/lib" CACHE PATH "Path to boost")

if(NOT DLIB_PATH)
	message(FATAL_ERROR "Missing dlib install path, please specify DLIB_PATH")
else()
  	message("dlib path is ${DLIB_PATH}")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)
find_package(Boost REQUIRED serialization)

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


add_executable(csv-dlib  "main.cc")
target_link_libraries(csv-dlib ${Boost_LIBRARIES} ${DLIB_PATH}/libdlib.a )


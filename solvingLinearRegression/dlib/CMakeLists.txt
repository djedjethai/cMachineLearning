cmake_minimum_required(VERSION 3.0)
project(simple_linear_regression)

# Specify the path to the directory containing libdlib.a
set(DLIB_PATH "/home/jerome/clibs/dlibBUILT/lib" CACHE PATH "Path to dlib")

if(NOT DLIB_PATH)
	message(FATAL_ERROR "Missing dlib install path, please specify DLIB_PATH")
else()
	message("dlib path is ${DLIB_PATH}")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# You should only use include_directories() if you want to add custom include directories that are not part of your project's source tree. However, since Dlib's header files are part of the library's installation and are usually available system-wide, you don't need to specify them with include_directories().
# include_directories(${DLIB_PATH})

add_executable(linear_regression "linearRegression_dlib.cc")
target_link_libraries(linear_regression ${DLIB_PATH}/libdlib.a)





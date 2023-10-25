cmake_minimum_required(VERSION 3.0)
project(fastCppCsvParser)


set(SHARK_PATH "/home/jerome/clibs/sharkBUILT" CACHE PATH "Path to shark")
set(Boost_LIBRARY_DIRS "/usr/lib" CACHE PATH "Path to boost")

# if(NOT EIGEN_PATH)
#   message(FATAL_ERROR "Missing Eigen install path, please specify EIGEN_PATH")
# else()
#   message("Eigen path is ${EIGEN_PATH}")
# endif()

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED serialization)

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

link_directories(${SHARK_PATH}/lib ${Boost_LIBRARY_DIRS})

add_executable(fast-csv  "main.cc")
target_link_libraries(fast-csv cblas ${Boost_LIBRARIES} ${SHARK_PATH}/lib/libshark.a )


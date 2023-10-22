cmake_minimum_required(VERSION 3.22)
project(PriCT)

find_library(GMP_LIB gmp)
#SET(CMAKE_BUILD_TYPE "Release")

add_executable(PriCT main.cpp)
#add_executable(PriCT IntervalCount.cpp)
#add_executable(PriCT PosPPtest.cpp)
#add_executable(PriCT FileTest.cpp)
#add_executable(PriCT LocationTest.cpp)
#add_executable(PriCT  SantiTest.cpp)
#add_executable(PriCT SOCI/Test.cpp)
target_link_libraries(PriCT ${GMP_LIB})
cmake_minimum_required(VERSION 3.28)


project(mlpa VERSION 0.0.1 DESCRIPTION "MLPA: Traits Based Pretty Logger for C++" LANGUAGES C++)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/) #append dir



# c++ variables
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # needed by clang-tidy
set(CMAKE_CXX_STANDARD C++20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Find requirements
find_package(Python3 REQUIRED COMPONENTS Interpreter)

include(BuildTools) # Include the Tools.cmake module: clang-format cmake-format clang-tidy commands
include(FetchGoogleTest)


enable_testing()


# create a header only library target
add_library(MLPALogger STATIC)

target_include_directories(MLPALogger PRIVATE "${CMAKE_SOURCE_DIR}/include/")

# add a tests subdirectory
add_subdirectory(test)
#Require a minimum version of cmake.
cmake_minimum_required(VERSION 3.15)
project(STB)

add_library(STB include/STB/stb_image.h include/STB/default.cpp)
target_include_directories(STB PUBLIC include/)

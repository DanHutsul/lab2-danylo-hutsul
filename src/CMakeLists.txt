cmake_minimum_required(VERSION 3.16)
project(my_str_library C)

set(CMAKE_C_STANDARD 11)

SET( my_lib_src my_library.c testing.c my_library.h)
ADD_LIBRARY(my_str_library SHARED ${my_lib_src} )
cmake_minimum_required(VERSION 3.14)
project(matlab_fuzzy C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(matlab_fuzzy
        fis.c
        fis.h
        fismain.c)

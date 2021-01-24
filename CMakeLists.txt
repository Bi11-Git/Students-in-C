cmake_minimum_required(VERSION 3.17)
project(Students_in_c C)

set(CMAKE_C_STANDARD 99)

add_executable(Students_in_c main.c students.c students.h)
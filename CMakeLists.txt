cmake_minimum_required(VERSION 3.13)
project(hanoi C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hanoi
        hanoi.c
        stack.c
        stack.h)

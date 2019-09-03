cmake_minimum_required(VERSION 3.10)
project(hw1)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(hw1
        minishell.c
        minishell.h)

target_link_libraries(hw1 PRIVATE -lcrypt)

cmake_minimum_required(VERSION 3.10)
project(OOP)

set(CMAKE_C_STANDARD 11)

add_executable(project
        main.c
        matrix.c
        field_info.c
        tests.c)

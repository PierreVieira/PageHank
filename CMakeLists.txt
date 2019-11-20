cmake_minimum_required(VERSION 3.15)
project(discretaPGR C)

set(CMAKE_C_STANDARD 99)

add_executable(discretaPGR main.c src/estruturas.h src/auxiliar.c src/auxiliar.h)
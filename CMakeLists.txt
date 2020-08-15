cmake_minimum_required(VERSION 3.15)
project(cryptography C)

set(CMAKE_C_STANDARD 11)

add_executable(cryptography main.c CRYPTOGRAPHY.c CRYPTOGRAPHY.h)



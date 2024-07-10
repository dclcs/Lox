cmake_minimum_required(VERSION 3.29)
project(clox)

set(CMAKE_CXX_STANDARD 20)

add_executable(clox main.c
        common.h
        chunk.h
        chunk.c
        memory.h
        memory.c
        debug.c
        debug.h
        value.c
        value.h
        vm.c
        vm.h)

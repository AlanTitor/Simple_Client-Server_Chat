cmake_minimum_required(VERSION 3.30)
project(chat)
set(CMAKE_C_STANDARD 23)
add_executable(chat src/main.c src/main.h test/test.c test/test.h include/include.h) 

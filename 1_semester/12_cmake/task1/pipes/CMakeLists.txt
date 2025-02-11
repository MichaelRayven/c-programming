# Задание: Создать библиотеку pipes из read_pipe.c write_pipe.c

cmake_minimum_required(VERSION 3.10)
project(pipes)	

set(SOURCE_LIB read_pipe.c write_pipe.c)	
add_library(PIPES_LIB SHARED ${SOURCE_LIB})
# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes

cmake_minimum_required(VERSION 3.10)
project(background)	

set(SOURCE_LIB background.c)	
add_library(BACKGROUND_LIB SHARED ${SOURCE_LIB})

target_link_libraries(BACKGROUND_LIB PIPES_LIB)
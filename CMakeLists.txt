cmake_minimum_required(VERSION 3.13)
project(cs201imdb C)

set(CMAKE_C_STANDARD 99)

add_executable(cs201imdb main.c display.c display.h libraries.h newCatalog.c newCatalog.h catalogs.c catalogs.h avlTree.c avlTree.h)
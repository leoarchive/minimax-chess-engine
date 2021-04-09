cmake_minimum_required(VERSION 3.17)
project(chess_engine C)

set(CMAKE_C_STANDARD 11)

add_executable(chess_engine src/main.c src/chess.c src/stack.c src/search.c)

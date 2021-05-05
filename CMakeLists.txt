cmake_minimum_required(VERSION 3.17)
project(chess_engine C)

set(CMAKE_C_STANDARD 11)

add_executable(chess_engine main.c chess.c minimax.c bitboard.c validation.c tables.c)

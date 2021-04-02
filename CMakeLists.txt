cmake_minimum_required(VERSION 3.17)
project(chess_engine C)

set(CMAKE_C_STANDARD 11)

add_executable(chess_engine
        chess.c
        stack.c
        rules/rules.c
        rules/white_pawn.c
        rules/black_pawn.c
        )

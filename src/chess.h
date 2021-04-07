/*
    Dumb, a chess engine
    Copyright (C) 2021 Leonardo Zamboni

    Dumb is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dumb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#include "stack.h"

#ifdef LINUX
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

#define WHT "\e[30;48;5;215m"
#define BLK "\e[30;48;5;208m"

enum pieces {empty,black_rook,black_knight,black_bishop,black_queen,black_king,black_bishop2,black_knight2,black_rook2,
        black_pawn1,black_pawn2,black_pawn3,black_pawn4,black_pawn5,black_pawn6,black_pawn7,black_pawn8,
        white_pawn1,white_pawn2,white_pawn3,white_pawn4,white_pawn5,white_pawn6,white_pawn7,white_pawn8,
        white_rook,white_knight,white_bishop,white_queen,white_king,white_bishop2,white_knight2,white_rook2,};

const char *AN[64];
const char *pieces[33];
unsigned int chessboard[64];
unsigned int bitboard[64];

bool turn;

void print_chessboard(void);
void print_bitboard(void);
void back_stack(Stack *s);
int move_piece(void);
int command_line(void);
int move_rules(const char *current_algebraic_notation, const char *new_algebraic_notation);
int get_chessboard_position(const char *piece_algebraic_notation);
int generic_rule_verify(const char *current_algebraic_notation, const char *new_algebraic_notation);
int bishop_validation(const char *current_algebraic_notation, const char *new_algebraic_notation);
int rook_validation(const char *current_algebraic_notation, const char *new_algebraic_notation);
int bishop_validation_verify(char *diagonal_algebraic_notation[], int current, int new);
int white_pawn_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int white_bishop_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int white_knight_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int white_rook_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int white_king_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int black_pawn_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int black_bishop_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int black_knight_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int black_rook_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);
int black_king_rule(const char *current_algebraic_notation, const char *new_algebraic_notation);

#endif
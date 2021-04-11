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
int move_piece(const char *current, const char *new);
int move_rules(const char *current_algebraic_notation, const char *new_algebraic_notation);
int get_chessboard_position(const char *piece_algebraic_notation);
int generic_rule_verify(const char *current_algebraic_notation, const char *new_algebraic_notation);
int bishop_validation(const char *current_algebraic_notation, const char *new_algebraic_notation);
int rook_validation(const char *current_algebraic_notation, const char *new_algebraic_notation);
int verify_validation(char *diagonal_algebraic_notation[], int current, int new);
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
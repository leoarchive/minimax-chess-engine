#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.c"

#ifdef LINUX
const char *pieces[] = {
        " ",
        "♜","♞","♝","♛","♚","♝","♞","♜",
        "♟","♟","♟","♟","♟","♟","♟","♟",
        "♙","♙","♙","♙","♙","♙","♙","♙",
        "♖","♘","♗","♕","♔","♗","♘","♖"
};
#define CLEAR "clear"
#else
const char *pieces[] = {
        " ",
        "R","N","B","Q","K","B","N","R",
        "P","P","P","P","P","P","P","P",
        "P","P","P","P","P","P","P","P",
        "R","N","B","Q","K","B","N","R"
};
#define CLEAR "cls"
#endif

#define WHT "\e[30;48;5;215m"
#define BLK "\e[30;48;5;208m"

const char *AN[] = {
        "a8","b8","c8","d8","e8","f8","g8","h8",
        "a7","b7","c7","d7","e7","f7","g7","h7",
        "a6","b6","c6","d6","e6","f6","g6","h6",
        "a5","b5","c5","d5","e5","f5","g5","h5",
        "a4","b4","c4","d4","e4","f4","g4","h4",
        "a3","b3","c3","d3","e3","f3","g3","h3",
        "a2","b2","c2","d2","e2","f2","g2","h2",
        "a1","b1","c1","d1","e1","f1","g1","h1"
};

enum pieces {empty,black_rook,black_knight,black_bishop,black_queen,black_king,black_bishop2,black_knight2,black_rook2,
        black_pawn1,black_pawn2,black_pawn3,black_pawn4,black_pawn5,black_pawn6,black_pawn7,black_pawn8,
        white_pawn1,white_pawn2,white_pawn3,white_pawn4,white_pawn5,white_pawn6,white_pawn7,white_pawn8,
        white_rook,white_knight,white_bishop,white_queen,white_king,white_bishop2,white_knight2,white_rook2,};

unsigned int chessboard[] = {
        black_rook,black_knight,black_bishop,black_queen,black_king,black_bishop2,black_knight2,black_rook2,
        black_pawn1,black_pawn2,black_pawn3,black_pawn4,black_pawn5,black_pawn6,black_pawn7,black_pawn8,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        white_pawn1,white_pawn2,white_pawn3,white_pawn4,white_pawn5,white_pawn6,white_pawn7,white_pawn8,
        white_rook,white_knight,white_bishop,white_queen,white_king,white_bishop2,white_knight2,white_rook2,
};

unsigned int bitboard[64];

bool turn = true;

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
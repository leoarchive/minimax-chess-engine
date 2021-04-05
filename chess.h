#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.c"
#include "rules.c"

#define WHT "\x1B[43m"
#define BLK "\x1B[42m"

bool turn = true;

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
        "R","K","B","Q","K","B","K","R",
        "P","P","P","P","P","P","P","P",
        "P","P","P","P","P","P","P","P",
        "R","K","B","Q","K","B","K","R"
};
#define CLEAR "cls"
#endif

void print_chessboard(void);
void print_bitboard(void);
int move_piece(void);
void back(Stack *s);
int command_line(void);
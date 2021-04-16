#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#include "stack.h"
#include "move.h"

#if defined LINUX || defined __APPLE__
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

#define WHITE_CASE_COLOR "\e[30;48;5;215m"
#define BLACK_CASE_COLOR "\e[30;48;5;208m"
#define DEFAULT_COLOR "\033[0m"
#define WHITE_PIECE_COLOR "\e[1;37m"

int from_value;
int to_value;
char from_char;
char to_char;
int to_cb_pos;

char *AN[64];
char *pieces[33];
int chessboard[64];

int bitboard[64];

bool player;

void print_chessboard(void);
void print_bitboard(void);

int move(void);
void back(Stack *s);

int get_position(char *p);
void get_bitboard(char *f);
int get_rules(char *f, char *t);

int pawn(void);
int bishop(char *f, char *t);
int knight(void);
int rook(char *f, char *t);
int queen(char *f, char *t);
int king(void);

#endif
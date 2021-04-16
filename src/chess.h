#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#if defined LINUX || defined __APPLE__
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

#define WHITE "\e[30;48;5;215m"
#define BLACK "\e[30;48;5;208m"
#define DEFAULT "\033[0m"
#define WHITE_PIECE "\e[1;37m"

#define SWAP_TURN player = !player;

int from_value;
int to_value;
char from_char;
char to_char;
int to_cb_pos;

char *AN[64];
char *pieces[33];
int board[64];

bool player;

void print_chessboard(void);
void print_bitboard(void);

int move(void);

int get_rules(char *f, char *t);
int get_position(char *p);

int pawn(void);
int bishop(char *f, char *t);
int knight(void);
int rook(char *f, char *t);
int queen(char *f, char *t);
int king(void);

#endif
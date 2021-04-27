#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#if defined LINUX
#define CLEAR "clear"
#define WINOUTPUT
#else
#include <windows.h>
#define CLEAR "cls"
#define WINOUTPUT SetConsoleOutputCP(65001);
#endif

#define W "\e[30;48;5;215m"
#define B "\e[30;48;5;208m"
#define WP "\e[1;97m"
#define BP ""
#define D "\033[0m"
#define SWAP_TURN player = !player;
#define color bool
#define white true

int from_value;
int to_value;
char from_char;
char to_char;
int to_pos;
int from_pos;

char *AN[64];
char *pieces[33];
int board[64];

bool player;

void print_chessboard(size_t i, int n, bool c);

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
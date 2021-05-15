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

#define WHITEBG "\e[30;48;5;215m"
#define BLACKBG "\e[30;48;5;208m"
#define WHITEPC "\e[1;97m"
#define BLACKPC ""
#define DEFAULT "\033[0m"

#define SWAP_TURN player = !player;
#define SAVE_BOARD unmove_board = board; 

#define color bool
#define white true

#define BLACKINIT 1
#define BLACKEND 16
#define WHITEINIT 17
#define WHITEEND 32

int from_value;
int to_value;
char from_char;
char to_char;
int to_pos;
int from_pos;

char *AN[64];
char *pieces[33];
int board[64];

int w_cap[32];
int b_cap[32];
int w_cnt;
int b_cnt;

bool player;

void print_chessboard(size_t i, int n, bool c);
void print_capture(void);

int move(void);
int un_move_board(void);

int get_rules(char *f, char *t);
int get_position(char *p);

int pawn(void);
int bishop(char *f, char *t);
int knight(void);
int rook(char *f, char *t);
int queen(char *f, char *t);
int king(void);

#endif

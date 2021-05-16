#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#ifdef __linux__
#define CLEAR "clear"
#define WINOUTPUT
#elif __WIN32__
#include <windows.h>
#define CLEAR "cls"
#define WINOUTPUT SetConsoleOutputCP(65001);
#else
    #error unsuported plataform
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

extern int from_value;
extern int to_value;
extern char from_char;
extern char to_char;
extern int to_pos;
extern int from_pos;

extern char *AN[64];
extern char *pieces[33];
extern int board[64];

extern int w_cap[32];
extern int b_cap[32];
extern int w_cnt;
extern int b_cnt;

extern bool player;

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

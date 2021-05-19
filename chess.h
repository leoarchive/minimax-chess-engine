#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#ifdef __linux__
	#define CLEAR "clear"
#elif __WIN32__
	#include <windows.h>
	#define CLEAR "cls"
	#define WIN_OUTPUT SetConsoleOutputCP(65001);
#else 
	#error unsuported plataform
#endif

#define WHITE_BACKGROUND "\e[30;48;5;215m"
#define BLACK_BACKGROUND "\e[30;48;5;208m"
#define WHITE_PIECE 	 "\e[1;97m"
#define BLACK_PIECE 	 ""
#define DEFAULT		 "\e[0m"

#define BLACK_PIECES_VALUE_MIN 1
#define BLACK_PIECES_VALUE_MAX 16
#define WHITE_PIECES_VALUE_MIN 17
#define WHITE_PIECES_VALUE_MAX 32

#define WHITE_KING_VALUE 29
#define BLACK_KING_VALUE 5

#define SWAP_PLAYER_TURN player = !player;

#define color bool
#define white true

extern int   	from_value;   
extern int   	to_value;
extern int   	from_position;
extern int   	to_position;
extern char  	from_char;
extern char  	to_char;

extern char* 	AN[64];
extern char* 	PIECES[33];
extern int   	board[64]; 
extern int 	aux_board[64];
extern int	bitboard[64]; 

extern int	white_captures_counter;
extern int	black_captures_counter;
extern int	white_captures[32];
extern int 	black_captures[32];   	
	
extern bool	player;

void print_chessboard_and_pieces(size_t s, int n, bool p);

int set_move(void);
int is_checkmate(int f, int t);
int get_rules(char* f, char* t);
int get_position_from_value(int p);
int get_position_from_char(char* p);
int pawn(void);
int bishop(char* f, char* t);
int knight(void);
int rook(char* f, char* t);
int queen(char* f, char* t);
int king(void);

void get_aux_board(void);
void set_aux_board(void);
void print_capture_pieces(void);
void set_bitboard(char* f);
void print_bitboard(void);

int _set_validation(char* v[], int f, int t);
int get_validation(char *f, char *t, bool r);


#endif

/*
 *  Minimax Chess Engine Algorithm 
 *  Copyright (c) 2020 Leonardo Zamboni
 * 
 *  this program is free software: you can redistribute it and/or modify
 *  it under the terms of the gnu general public license as published by
 *  the free software foundation, either version 3 of the license, or
 *  (at your option) any later version.
 *  
 *  this program is distributed in the hope that it will be useful,
 *  but without any warranty; without even the implied warranty of
 *  merchantability or fitness for a particular purpose.  see the
 *  gnu general public license for more details.
 *  
 *  you should have received a copy of the gnu general public license
 *  along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */ 
#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#ifdef __linux__
	#define CLEAR "clear"
	#define WIN_OUTPUT printf("not windows os\n");
#elif __WIN32__
	#include <windows.h>
	#define CLEAR "cls"
	#define WIN_OUTPUT SetConsoleOutputCP(65001);
#else 
	#error unsuported plataform
#endif

#define WHITE_BACKGROUND 	"\e[30;48;5;215m"
#define BLACK_BACKGROUND 	"\e[30;48;5;208m"
#define WHITE_PIECE 	 	"\e[1;97m"
#define BLACK_PIECE 	 	""
#define DEFAULT		 	"\e[0m"

#define BLACK_PIECES_VALUE_MIN 1
#define BLACK_PIECES_VALUE_MAX 16
#define WHITE_PIECES_VALUE_MIN 17
#define WHITE_PIECES_VALUE_MAX 32

#define WHITE_KING_VALUE 	29
#define BLACK_KING_VALUE 	5

#define SWAP_PLAYER_TURN player = !player;

#define color 	bool
#define white 	true

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
void print_capture_pieces(void);
void print_bitboard(void);

int set_move(void);
int _set_validation(char* v[], int f, int t);
void set_aux_board(void);
void set_bitboard(char* f);

int get_rules(char* f, char* t);
int get_position_from_value(int p);
int get_position_from_char(char* p);
int get_validation(char *f, char *t, bool r);
void get_aux_board(void);

int is_checkmate(int f, int t);

int pawn(void);
int bishop(char* f, char* t);
int knight(void);
int rook(char* f, char* t);
int queen(char* f, char* t);
int king(void);


#endif

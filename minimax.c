#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chess.h"
#include "minimax.h"

#define WHITE_PAWN 	10
#define WHITE_KNIGHT 	30
#define WHITE_BISHOP 	30
#define WHITE_ROOK 	50
#define WHITE_QUEEN 	90
#define WHITE_KING      900
#define BLACK_PAWN     	-10
#define BLACK_KNIGHT 	-30
#define BLACK_BISHOP 	-30
#define BLACK_ROOK	-50
#define BLACK_QUEEN	-90
#define BLACK_KING 	-900

#define INFINITY	99999
#define DEPTH		3
#define TIMES		32

int list_from_moves[TIMES];
int list_to_moves[TIMES];
int list_evaluates[TIMES];
int list_counter = 0;
int from_aux;
int to_aux;

int main(void) {
	WIN_OUTPUT
	system(CLEAR);
	srand(time(NULL));

	print_chessboard_and_pieces(0, 8, false);
	while (1) {
		puts("");
		int m = set_move();
		if 	(m == 1) continue;
		else if (m == 2) return 0;
		puts("");
		system(CLEAR);
		get_move_generation();
		list_print();
		print_chessboard_and_pieces(0, 8, false);	
	}
}

void list_moves_init(void) {
	for (size_t i = 0; i < TIMES; ++i) {
		list_from_moves[i] 	= 0;
		list_to_moves[i] 	= 0;
	} 
}

int list_moves_check(int f, int t) {
	for (size_t i = 0; i < TIMES; ++i) if (list_from_moves[i] == f && list_to_moves[i] == t) return 1;
	return 0;
}

void list_print(void) {
	for (size_t i = 0; i < TIMES; ++i) 
		printf("%d from %s to %s eval %d\n", i, PIECES[list_from_moves[i]], AN[list_to_moves[i]], list_evaluates[i]);
}

void _set_move(int f, int t) {
	board[t] = board[f];
	board[f] = 0;
	SWAP_PLAYER_TURN
}

int get_evaluate(void) {
	int white_evaluate = 0;
	int black_evaluate = 0;
	for (int i = 0; i < 64; ++i) {
		if 	(board[i] > BLACK_PIECES_VALUE_MAX) 	white_evaluate += get_value(i, i);
		else if (board[i]) 				black_evaluate -= get_value(i, i);
	}
	if (player) 	return white_evaluate - black_evaluate;
	else		return black_evaluate + white_evaluate;
}


void get_move_generation(void) {
	set_aux_board();
	list_moves_init();
	list_counter = 0;
	for (size_t i = 0; i < TIMES; ++i) list_evaluates[i] = 0;

	int eval;	
	int from;
	int to;
	int min 	= INFINITY;
	int max 	= -INFINITY;
	
	for (size_t i = 0; i < TIMES; ++i) {
		eval 		  = minimax(DEPTH);
		list_evaluates[i] = eval;
		if (player && eval > max) {
			max 	= eval;	
			from 	= from_aux;
			to 	= to_aux;
		}
		else if (eval < min) {
			min 	= eval;
			from 	= from_aux;
			to 	= to_aux;
		}
		get_aux_board();
	}

	int piece_value = get_position_from_value(from);
	set_bitboard(AN[piece_value]);
	printf("black: %s %s\n", AN[piece_value], AN[to]);

	if (board[to]) {
		if (player) white_captures[white_captures_counter++] = board[to];
		else 	    black_captures[black_captures_counter++] = board[to];
	}

	print_capture_pieces();
	_set_move(piece_value, to);
}

int minimax(int d) {
	if (!d) return get_evaluate();
	
	Move get;
	get = get_move();
	if (d == DEPTH) {
		if (list_moves_check(get.from, get.to)) get = get_move_aleatory(BLACK_PIECES_VALUE_MIN, BLACK_PIECES_VALUE_MAX);
		from_aux 	= get.from;
		to_aux 		= get.to;
		list_from_moves[list_counter] 	= from_aux;
		list_to_moves[list_counter] 	= to_aux;
		list_counter++;
	}
	
	_set_move(get_position_from_value(get.from), get.to);
	print_chessboard_and_pieces(0, 8, false);
	system(CLEAR);
	get = get_move();
	_set_move(get_position_from_value(get.from), get.to);
	print_chessboard_and_pieces(0, 8, false);
	system(CLEAR);
	return minimax(d - 1);
}

Move get_move(void) {
	Move get;
	int min = 0;
	int max = 0;
	int eval;
	int min_piece;
	int max_piece;
	bool end;
	
	if (player) {
		min_piece = WHITE_PIECES_VALUE_MIN;
		max_piece = WHITE_PIECES_VALUE_MAX;
	}
	else {
		min_piece = BLACK_PIECES_VALUE_MIN;
		max_piece = BLACK_PIECES_VALUE_MAX;
	}
	
	for (int i = min_piece; i <= max_piece; ++i) {
		set_bitboard(AN[get_position_from_value(i)]);
		for(int j = 0; j < 64; ++j) {
			if (bitboard[j]) {
				eval = get_value(j, j);
				if (player) {
					if (eval < min) {
						get.from = i;
						get.to 	 = j;
						min 	 = eval;
						end 	 = true;
					}
				}
				else {
					if (eval > max) {
						get.from = i;
						get.to   = j;
						max 	 = eval;
						end 	 = true;
					}
				}
			}
		}
	}
	if (!end) return get_move_aleatory(min_piece, max_piece);
	return get;
}

Move get_move_aleatory(int min_piece, int max_piece) {
	Move get;
	bool end;
	int eval;

	do {
		int min 	= INFINITY;
		int max 	= -INFINITY;
		get.from 	= 0;

		while (get.from < min_piece) get.from = rand() % max_piece;

		set_bitboard(AN[get_position_from_value(get.from)]);
		for (int i = 0; i < 64; ++i) {
			if (bitboard[i]) {
				eval = get_value(get_position_from_value(get.from), i);
				if (player) {
					if (eval > max) {
						get.to 	= i;
						max	= eval;
					}
				}
				else {
					if (eval < min) {
						get.to 	= i;
						min 	= eval;
					}
				}
				end = true;	
			}
		}
	} while (!end);
	return get;			
}

int get_value(int p, int s) {
	double white_king[] = {
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
       	 	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
        	-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
        	-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
         	 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0,
         	 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0
	};
	double white_queen[] = {
        	-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
        	-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
        	-1,0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
        	-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
         	 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
        	-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
        	-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
        	-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0
	};
	double white_rook[] = {
         	 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
         	 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
       		-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
       	 	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
         	 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0
	};
	double white_bishop[] = {
        	-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
        	-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
        	-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
        	-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
        	-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
        	-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
        	-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
        	-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0
	};
	double white_knight[] = {
        	-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
        	-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
        	-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
        	-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
        	-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
        	-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
        	-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
        	-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
	};
	double white_pawn[] = {
        	 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
         	 5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
         	 1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
         	 0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
         	 0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
         	 0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
         	 0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5,
         	 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0
	};
	double black_king[] = {
         	 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0,
         	 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0,
        	-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
        	-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
        	-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
	};
	double black_queen[] = {
       	 	-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
        	-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
        	-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
         	 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
        	-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
        	-1,0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
        	-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
        	-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
	};
	double black_rook[] = {
         	 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
        	-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
         	 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
         	 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
	};
	double black_bishop[] = {
        	-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
        	-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
        	-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
        	-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
        	-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
       		-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
       		-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
        	-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
	};
	double black_knight[] = {
        	-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
        	-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
        	-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
       		-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
        	-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
        	-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
        	-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
        	-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
	};
	double black_pawn[] = {
        	0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
        	0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5,
        	0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
        	0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
        	0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
        	1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
        	5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
        	0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
	};
	if  	(board[p] > 8 && board[p] < 17)  return BLACK_PAWN - black_pawn[s]; 
	else if (board[p] > 16 && board[p] < 25) return WHITE_PAWN + white_pawn[s];
	switch  (board[p]) {
		case 1: case 8: 	return BLACK_ROOK   - black_rook[s];
		case 2: case 7: 	return BLACK_KNIGHT - black_knight[s];
		case 3: case 6: 	return BLACK_BISHOP - black_bishop[s];
		case 4:			return BLACK_QUEEN  - black_queen[s];
		case 5:			return BLACK_KING   - black_king[s];
		case 25: case 32:	return WHITE_ROOK   + white_rook[s];
		case 26: case 31:	return WHITE_KNIGHT + white_knight[s];
		case 27: case 30:	return WHITE_BISHOP + white_bishop[s];
		case 28: 		return WHITE_QUEEN  + white_queen[s];
		case 29: 		return WHITE_KING   + white_king[s];	
	}	
	return 0;
} 

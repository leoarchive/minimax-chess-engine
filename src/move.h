#ifndef SEARCH_H
#define SEARCH_H

#include "chess.h"

#define WHITE_STRENGTH_PAWN 10
#define WHITE_STRENGTH_KNIGHT 30
#define WHITE_STRENGTH_BISHOP 30
#define WHITE_STRENGTH_ROOK 50
#define WHITE_STRENGTH_QUEEN 90
#define WHITE_STRENGTH_KING 900

#define BLACK_STRENGTH_PAWN (-10)
#define BLACK_STRENGTH_KNIGHT (-30)
#define BLACK_STRENGTH_BISHOP (-30)
#define BLACK_STRENGTH_ROOK (-50)
#define BLACK_STRENGTH_QUEEN (-90)
#define BLACK_STRENGTH_KING (-900)

int bitboard_fixed[64];

void print_fixed_bitboard(void);
int move_generation(void);
void best_position_and_piece(void);
int get_piece_strength(int piece);
void fixed_bitboard(char *current);

#endif
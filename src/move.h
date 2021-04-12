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

int move_generation(void);
int get_piece_strength(int piece);
int get_best_position(int piece);

#endif
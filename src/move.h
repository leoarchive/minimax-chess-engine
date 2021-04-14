#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <stdlib.h>

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

#define INFINITY 999999

int best_piece;
int best_position;
int minimax_best_piece;
int minimax_best_move;

void make_move_acb(void);
void pass_cb(void);
void make_move(void);
int minimax(int d);
int move_generation(void);
void best_position_and_piece(void);
void aleatory_position(void);
int get_cposition(int piece);
int get_evaluation(int piece);

#endif
#ifndef MOVE_H
#define MOVE_H
#include "chess.h"

int make_move(void);
int move_generation(void);
void best_position_and_piece(void);
void aleatory_position(void);
int get_cposition(int piece);
int get_evaluation(int piece);

#endif
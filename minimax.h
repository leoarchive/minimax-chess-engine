/*
 *  Minimax Chess Engine Algorithm 
 *  Copyright (c) 2021 Leonardo Zamboni
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
#ifndef MINIMAX_H
#define MINIMAX_H

typedef struct moves{
	int from;
	int to;
}Move;

void list_moves_init(void);
int list_moves_check(int f, int t);
void list_print(void);

void _set_move(int f, int t);
int get_evaluate(void);
void get_move_generation(void);

int minimax(int d);

Move get_move(void); 
Move get_move_aleatory(int min_piece, int max_piece);

int get_value(int p, int s);


#endif

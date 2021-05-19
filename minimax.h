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

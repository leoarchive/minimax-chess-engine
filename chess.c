#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"
#include "validation.h"
#include "bitboard.h"

char *pieces[] = {" ",
	"♜","♞","♝","♛","♚","♝","♞","♜",
	"♟","♟","♟","♟","♟","♟","♟","♟",
	"♙","♙","♙","♙","♙","♙","♙","♙",
	"♖","♘","♗","♕","♔","♗","♘","♖"
};

char *AN[] = {
	"a8","b8","c8","d8","e8","f8","g8","h8",
	"a7","b7","c7","d7","e7","f7","g7","h7",
	"a6","b6","c6","d6","e6","f6","g6","h6",
	"a5","b5","c5","d5","e5","f5","g5","h5",
	"a4","b4","c4","d4","e4","f4","g4","h4",
	"a3","b3","c3","d3","e3","f3","g3","h3",
	"a2","b2","c2","d2","e2","f2","g2","h2",
	"a1","b1","c1","d1","e1","f1","g1","h1"
};

int board[] = {
	1,2,3,4,5,6,7,8,
	9,10,11,12,13,14,15,16,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	17,18,19,20,21,22,23,24,
	25,26,27,28,29,30,31,32
};

color player = white;
int w_cnt = 0;
int b_cnt = 0;

void print_chessboard(size_t i, int n, bool c) {
	if (i == 64) {
		printf("\n  ");
		char l = 'a';
		while (l != 'i')
			printf("%c ", l++);
		return;
	}
	else if (!i)
		printf("%d ", n--);
	else if (!(i % 8))
		printf("\n%d ", n--);
	else
		c = !c;
	printf("%s%s%s "DEFAULT, c ? BLACKBG : WHITEBG, board[i] < 17 ? BLACKPC : WHITEPC, pieces[board[i]]);
	print_chessboard(++i, n, c);
}

int move(void) {
	char *from = (char *) malloc(2 * sizeof(char));
	char *to = (char *) malloc(2 * sizeof(char));
	print_capture();
	printf("%s: ", player ? "white" : "black");
	scanf(" %s %s", from, to);

	if (!strcmp(from,"e"))
		return 2;

	set_bitboard(from);
	//print_bitboard();
	int from_pos_m = get_position(from);
	int to_pos_m = get_position(to);

	if (!bitboard[to_pos_m]) {
		printf("invalid move");
		return 1;
	}
	else if (board[to_pos_m]) {
		if (player)
			w_cap[w_cnt++] = board[to_pos_m];
		else
			b_cap[b_cnt++] = board[to_pos_m];
	}

	board[to_pos_m] = board[from_pos_m],
	board[from_pos_m] = 0;
	SWAP_TURN
		return 0;
}

int get_rules(char *f, char *t) {
	if (!strcmp(f, t))
		return 0;
	from_value = f[1] - '0',
		   to_value = t[1] - '0',
		   from_char = f[0],
		   to_char = t[0],
		   from_pos = board[get_position(f)],
		   to_pos = board[get_position(t)];
		   if (!from_pos)
			   return 0;

		   if (player) {
			   if (from_pos < 17 || to_pos > 16)
				   return 0;
		   }
		   else {
			   if (from_pos > 16 || to_pos && to_pos < 17)
				   return 0;
		   }

		   if (from_pos > 16 && from_pos < 25 || from_pos > 8 && from_pos < 17)
			   return pawn();
		   else if (from_pos == 27 || from_pos == 30 || from_pos == 3 || from_pos == 6)
			   return bishop(f, t);
		   else if (from_pos == 26 || from_pos == 31 || from_pos == 2 || from_pos == 7)
			   return knight();
		   else if (from_pos == 25 || from_pos == 32 || from_pos == 1 || from_pos == 8)
			   return rook(f, t);
		   else if (from_pos == 28 || from_pos == 4)
			   return queen(f, t);
		   else if (from_pos == 29 || from_pos == 5)
			   return king();
		   return 1;
}

int get_position(char *p) {
	for (int i = 0; i < 64; ++i)
		if (!strcmp(AN[i], p))
			return i;
	return 0;
}

int pawn(void) {
	bool two_square = false;
	if (player) {
		if (from_value == 2)
			two_square = true;
		if (to_pos && to_pos < 17 && to_char == from_char || to_value < from_value)
			return 0;
	}
	else {
		if (from_value == 7)
			two_square = true;
		if (to_pos > 16 && to_char == from_char || to_value > from_value)
			return 0;
	}

	if (two_square) {
		if (player) {
			if (to_value != 3 && to_value != 4)
				return 0;
		}
		else {
			if (to_value != 6 && to_value != 5)
				return 0;
		}
	}
	else {
		if (player) {
			if (to_value > (from_value + 1))
				return 0;
		}
		else {
			if (to_value < (from_value - 1))
				return 0;
		}
	}

	if (to_char != from_char) {
		if (to_char != (from_char + 1) && to_char != (from_char - 1) || from_value == to_value)
			return 0;
		if (player) {
			if (to_pos > 16 || to_value > (from_value + 1))
				return 0;
		}
		else {
			if (to_pos && to_pos < 17 || to_value < (from_value - 1))
				return 0;
		}
		if (!to_pos)
			return 0;
	}
	return 1;
}

int bishop(char *f, char *t) {
	int v = validation(f, t, false);
	if (to_char == from_char || v == 1 || v && v != get_position(t))
		return 0;

	int c = 0; char l;
	if (to_char > from_char) {
		l = from_char;
		while (l++ != to_char)
			c++;
	}
	else {
		l = from_char;
		while (l-- != to_char)
			c++;
	}

	if (to_value == (from_value + c) || to_value == (from_value - c))
		return 1;
	return 0;
}

int knight(void) {
	if (to_value == (from_value + 2) && to_char == (from_char + 1)
			|| to_value == (from_value + 2) && to_char == (from_char - 1)
			|| to_value == (from_value - 2) && to_char == (from_char - 1)
			|| to_value == (from_value - 2) && to_char == (from_char + 1)
			|| to_char == (from_char + 2) && to_value == (from_value + 1)
			|| to_char == (from_char + 2) && to_value == (from_value - 1)
			|| to_char == (from_char - 2) && to_value == (from_value - 1)
			|| to_char == (from_char - 2) && to_value == (from_value + 1))
		return 1;
	return 0;
}

int rook(char *f, char *t) {
	int v = validation(f, t, true);
	if (to_value != from_value && to_char != from_char || v == 1 || v && v != get_position(t))
		return 0;
	return 1;
}

int queen(char *f, char *t) {
	if (!rook(f, t) && !bishop(f, t))
		return 0;
	return 1;
}

int king(void) {
	if (to_value == (from_value + 1) && to_char == (from_char + 1)
			|| to_value == (from_value + 1) && to_char == (from_char - 1)
			|| to_value == (from_value - 1) && to_char == (from_char - 1)
			|| to_value == (from_value - 1) && to_char == (from_char + 1)
			|| to_value == from_value && to_char == (from_char + 1)
			|| to_value == from_value && to_char == (from_char - 1)
			|| to_value == (from_value + 1) && to_char == from_char
			|| to_value == (from_value - 1) && to_char == from_char)
		return 1;
	return 0;
}

void print_capture(void) {
	if (player) {
		for (int i = 0; i < w_cnt; ++i)
			printf("%s ", pieces[w_cap[i]]);
	}
	else {
		for (int i = 0; i < b_cnt; ++i)
			printf("%s ", pieces[b_cap[i]]);
	}
	puts("");
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "chess.h"
#include "minimax.h"
#include "bitboard.h"

int main(void) {
	WINOUTPUT
	system(CLEAR);
	srand(time(NULL));

	print_chessboard(0, CHAR_BIT, false);
	while (1) {
		puts("");
		int m = move();
		if (m == 1)
			continue;
		else if (m == 2)
			return 0;
		puts("");
		system(CLEAR);
		move_generation();
		print_chessboard(0, CHAR_BIT, false);
		//LIST_print();
		//print_bitboard();
	}
}

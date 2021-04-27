#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "chess.h"
#include "move.h"
#include "bitboard.h"

int main(void) {
    WINOUTPUT
    system(CLEAR);
    srand(time(NULL));

    print_chessboard(0, CHAR_BIT, false);
    while (1) {
        puts("");
        if (move())
            continue;
        system(CLEAR);
        move_generation();
        print_chessboard(0, CHAR_BIT, false);
        print_bitboard();
    }
}
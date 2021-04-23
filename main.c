#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "chess.h"
#include "move.h"

int main(void) {
    system(CLEAR);
    srand(time(NULL));

    while (1) {
        print_chessboard(0, CHAR_BIT, false);
        puts("");
        move();
        move_generation();
        //system(CLEAR);
    }
}
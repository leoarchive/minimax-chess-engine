#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "chess.h"
#include "stack.h"
#include "bitboard.h"
#include "move.h"

int main(void) {
    system(CLEAR);
    srand(time(NULL));
    //Stack *s = create();
    print_chessboard(0, CHAR_BIT, false);
    //push(s, board);

    while (1) {
        puts("");
        move();
        //push(s, board);
        set_move();
        //push(s, board);
        system(CLEAR);
        print_chessboard(0, CHAR_BIT, false);
    }
}
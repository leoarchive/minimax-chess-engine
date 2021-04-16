#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chess.h"
#include "stack.h"
#include "bitboard.h"
#include "move.h"

int main(void) {
    system(CLEAR);
    srand(time(NULL));
    Stack *s = create();
    print_chessboard();
    push(s, board);

    char i;
    while (1) {
        printf("\n'h' for help: ");
        scanf(" %c", &i);
        switch (i) {
            case 'b':
                back(s);
                break;
            case 'm':
                if (move())
                    continue;
                push(s, board);
                break;
            case 'h':
                puts("https://github.com/leozamboni/dumb-chess-engine");
                continue;
            case 'i':
                print_bitboard();
                continue;
            case 'e':
                return 0;
            default:
                continue;
        }
        if (!player)
            generation();
        print_chessboard();
    }
}
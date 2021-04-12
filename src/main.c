#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "search.h"

int main(void) {
    system(CLEAR);
    Stack *s = create_stack();
    print_chessboard();
    push_stack(s, chessboard);

    char i;
    while (1) {
        printf("\n'h' for help: ");
        scanf(" %c", &i);
        switch (i) {
            case 'b':
                back_stack(s);
                break;
            case 'm':
                if (move_piece())
                    continue;
                push_stack(s, chessboard);
                break;
            case 'h':
                puts("https://github.com/leozamboni/dumb-chess-engine");
                continue;
            case 'i':
                print_bitboard();
                continue;
            case 'g':
                break;
            case 'e':
                return 0;
            default:
                continue;
        }
        //system(CLEAR);
        print_chessboard();
    }
}
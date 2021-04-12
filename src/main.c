#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chess.h"
#include "move.h"

int main(void) {
    system(CLEAR);
    srand(time(NULL));
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
            case 'e':
                return 0;
            default:
                continue;
        }
        if (!turn)
            move_generation();
        //system(CLEAR);
        print_chessboard();
    }
}
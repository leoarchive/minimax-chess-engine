#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "search.h"

int main(void) {
    system(CLEAR);
    Stack *s = create_stack();
    print_chessboard();
    push_stack(s, chessboard);

    char *i = (char *) malloc(sizeof(char));
    while (1) {
        printf("\n'h' for help: ");
        scanf(" %c", i);
        switch (i[0]) {
            case 'b':
                back_stack(s);
                break;
            case 'm':
                if (move_piece(NULL, NULL))
                    continue;
                push_stack(s, chessboard);
                break;
            case 'c':
                output_stack(s);
                continue;
            case 'h':
                puts("https://github.com/leozamboni/dumb-chess-engine");
                continue;
            case 'u':
                print_bitboard();
                continue;
            case 'd':
                bpp = 0;
                search(s);
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